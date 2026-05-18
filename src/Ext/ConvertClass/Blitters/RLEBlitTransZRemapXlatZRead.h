#pragma once

#include "Blitter.h"

DEFINE_RLE_BLITTER(RLEBlitTransZRemapXlatZRead, BlitterPixelByteAndWord)
{
public:
	inline explicit RLEBlitTransZRemapXlatZRead(byte** remapData, T* data) noexcept
	{
		this->RemapData = remapData;
		this->PaletteData = data;
	}

	virtual ~RLEBlitTransZRemapXlatZRead() override final = default;

	virtual void Blit_Copy(void* dst, byte* src, int len, int line, int zbase, WORD* zbuf, WORD* abuf, int alvl, int warp, byte* zadjust)
	{
		Blit_Impl(dst, src, len, line, zbase, zbuf, abuf, alvl, warp, zadjust);
	}

	virtual void Blit_Copy_Tinted(void* dst, byte* src, int len, int line, int zbase, WORD* zbuf, WORD* abuf, int alvl, int warp, byte* zadjust, WORD tint)
	{
		Blit_Impl(dst, src, len, line, zbase, zbuf, abuf, alvl, warp, zadjust);
	}

private:
	__forceinline void Blit_Impl(void* dst, byte* src, int len, int line, int zbase, WORD* zbuf, WORD* abuf, int alvl, int warp, byte* zadjust)
	{
		T* pDest = reinterpret_cast<T*>(dst);
		byte** pRemapData = this->RemapData;
		T* pPaletteData = this->PaletteData;

		RLE_PROCESS_PRE_LINES(true, false, pDest, src, len, line, zbuf, abuf);

		// AVX2 BYTE
		if constexpr (Level == Simd::Level::AVX2 && std::is_same_v<T, BYTE> && CompileAvx2)
		{
			constexpr int ChunkSize = 8;
			constexpr uintptr_t ChunkBytes = ChunkSize * sizeof(WORD);
			alignas(32) unsigned int paletteLut32[256];
			Avx2_BuildByteLut32(pPaletteData, paletteLut32);
			alignas(32) unsigned int remappedIndices[8];
			ZBuffer* pZBuffer = ZBuffer::Instance;
			const uintptr_t zTailAddress = reinterpret_cast<uintptr_t>(pZBuffer->BufferTail);
			const __m256i zbaseVec = _mm256_set1_epi32(zbase);

			while (len > 0)
			{
				byte srcv = *src++;
				if (srcv)
				{
					byte* pRunSrc = src - 1;
					byte* pRunZAdjust = zadjust;
					int runLen = 1;
					while (runLen < len && pRunSrc[runLen])
						++runLen;

					int remaining = runLen;
					while (remaining >= ChunkSize)
					{
						const uintptr_t zAddress = reinterpret_cast<uintptr_t>(zbuf);
						if (zAddress + ChunkBytes > zTailAddress)
							break;

						const __m128i zAdjustBytes = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(pRunZAdjust));
						const __m256i zValues = _mm256_sub_epi32(zbaseVec, _mm256_cvtepi8_epi32(zAdjustBytes));
						const __m256i zbufValues = _mm256_cvtepu16_epi32(_mm_loadu_si128(reinterpret_cast<const __m128i*>(zbuf)));
						const __m256i zMask32 = _mm256_cmpgt_epi32(zbufValues, zValues);
						const int zMask = _mm256_movemask_ps(_mm256_castsi256_ps(zMask32));

						if (zMask)
						{
							byte* pCurrentRemap = *pRemapData;
							for (int lane = 0; lane < ChunkSize; ++lane)
								remappedIndices[lane] = pCurrentRemap[pRunSrc[lane]];

							const __m256i remapIndex32 = _mm256_load_si256(reinterpret_cast<const __m256i*>(remappedIndices));
							const __m256i index32 = remapIndex32;
							const __m256i value32 = _mm256_i32gather_epi32(reinterpret_cast<const int*>(paletteLut32), index32, 4);
							const __m128i value8 = Avx2_PackU32ToU8(value32);
							Avx2_StoreMask8(pDest, zMask, value8);
						}

						pRunSrc += ChunkSize;
						pRunZAdjust += ChunkSize;
						pDest += ChunkSize;
						zbuf += ChunkSize;
						remaining -= ChunkSize;
						ADJUST_POINTER(pZBuffer, zbuf);
					}

					while (remaining--)
					{
						int zval = zbase - static_cast<int>(static_cast<signed char>(*pRunZAdjust++));
						if (zval < *zbuf)
						{
							if constexpr (false)
								*pDest = pPaletteData[*pRunSrc];
							else if constexpr (false)
								*pDest = pRemapDest[*pDest];
							else if constexpr (false)
								*pDest = pPaletteData[pRemapData[*pRunSrc]];
							else
								*pDest = pPaletteData[(*pRemapData)[*pRunSrc]];
						}

						++pRunSrc;
						++pDest;
						++zbuf;
						ADJUST_POINTER(pZBuffer, zbuf);
					}

					src = pRunSrc;
					zadjust = pRunZAdjust;
					len -= runLen;
				}
				else
				{
					byte off = *src++;
					len -= off;
					pDest += off;
					zbuf += off;
					zadjust += off;
					ADJUST_POINTER(pZBuffer, zbuf);
				}
			}

			return;
		}

		// Scalar
		auto handler = [pRemapData, pPaletteData](T& dest, byte srcv, int zbase, WORD zbufv, byte zadjustv)
		{
			int zval = zbase - static_cast<int>(static_cast<signed char>(zadjustv));
			if (zval < zbufv)
				dest = pPaletteData[(*pRemapData)[srcv]];
		};

		RLE_PROCESS_PIXEL_DATAS(true, false, pDest, src, len, zbase, zbuf, abuf, zadjust, handler);
	}
	byte** RemapData;
	T* PaletteData;
};
