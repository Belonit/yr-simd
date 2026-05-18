#pragma once

#include "Blitter.h"

DEFINE_RLE_BLITTER(RLEBlitTransXlatAlphaZReadWrite, BlitterPixelWordOnly)
{
public:
	inline explicit RLEBlitTransXlatAlphaZReadWrite(WORD* data, int shadecount) noexcept
	{
		this->PaletteData = data;
		this->AlphaRemapper = AlphaLightingRemapClass::FindOrAllocate(shadecount);
	}

	virtual ~RLEBlitTransXlatAlphaZReadWrite() override final = default;

	virtual void Blit_Copy(void* dst, byte* src, int len, int line, int zbase, WORD* zbuf, WORD* abuf, int alvl, int warp, byte* zadjust)
	{
		Blit_Impl<false>(dst, src, len, line, zbase, zbuf, abuf, alvl, warp, zadjust, 0);
	}

	virtual void Blit_Copy_Tinted(void* dst, byte* src, int len, int line, int zbase, WORD* zbuf, WORD* abuf, int alvl, int warp, byte* zadjust, WORD tint)
	{
		Blit_Impl<true>(dst, src, len, line, zbase, zbuf, abuf, alvl, warp, zadjust, tint);
	}

private:
	template<bool UseTint>
	__forceinline void Blit_Impl(void* dst, byte* src, int len, int line, int zbase, WORD* zbuf, WORD* abuf, int alvl, int warp, byte* zadjust, WORD tint)
	{
		WORD* pDest = reinterpret_cast<WORD*>(dst);
		WORD* pAData = LOOKUP_ALPHA_REMAPPER(alvl, this->AlphaRemapper);
		WORD* pPaletteData = this->PaletteData;

		RLE_PROCESS_PRE_LINES(true, true, pDest, src, len, line, zbuf, abuf);

		// AVX2
		if constexpr (Level == Simd::Level::AVX2 && CompileAvx2)
		{
			constexpr int ChunkSize = 8;
			constexpr uintptr_t ChunkBytes = ChunkSize * sizeof(WORD);
			ZBuffer* pZBuffer = ZBuffer::Instance;
			ABuffer* pABuffer = ABuffer::Instance;
			const uintptr_t zTailAddress = reinterpret_cast<uintptr_t>(pZBuffer->BufferTail);
			const uintptr_t aTailAddress = reinterpret_cast<uintptr_t>(pABuffer->BufferTail);
			const __m256i zbaseVec32 = _mm256_set1_epi32(zbase);
			const __m256i low16Mask32 = _mm256_set1_epi32(0xFFFF);
			const __m256i tintVec32 = _mm256_set1_epi32(static_cast<int>(tint));

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
						const uintptr_t aAddress = reinterpret_cast<uintptr_t>(abuf);
						if (zAddress + ChunkBytes > zTailAddress || aAddress + ChunkBytes > aTailAddress)
						{
							break;
						}

						const __m256i zAdjust32 = _mm256_cvtepi8_epi32(_mm_loadl_epi64(reinterpret_cast<const __m128i*>(pRunZAdjust)));
						const __m256i zValues32 = _mm256_sub_epi32(zbaseVec32, zAdjust32);
						const __m256i zbuf32 = Avx2_Load8WordAsEpi32(zbuf);
						const __m256i zMask32 = _mm256_cmpgt_epi32(zbuf32, zValues32);

						if (_mm256_movemask_epi8(zMask32))
						{
							const __m256i srcIndices = Avx2_Expand8ToEpi32(pRunSrc);
							const __m256i alphaIndex32 = Avx2_Load8WordAsEpi32(abuf);
							const __m256i alphaValue32 = Avx2_GatherWordTable256(alphaIndex32, pAData);
							const __m256i paletteIndex32 = _mm256_or_si256(srcIndices, alphaValue32);
							__m256i result32 = Avx2_GatherWordTable(paletteIndex32, pPaletteData, 0xFFFF);

							if constexpr (UseTint)
							{
								result32 = _mm256_or_si256(result32, tintVec32);
							}

							const __m128i result16 = Avx2_PackU32ToU16(result32);
							const __m128i writeMask16 = Avx2_PackMask32ToI16(zMask32);
							const __m128i oldValue16 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(pDest));
							const __m128i blended16 = Avx2_BlendU16(oldValue16, result16, writeMask16);

							const __m256i zWrite32 = _mm256_and_si256(zValues32, low16Mask32);
							const __m128i zWrite16 = Avx2_PackU32ToU16(zWrite32);
							const __m128i oldZ16 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(zbuf));
							const __m128i zBlended16 = Avx2_BlendU16(oldZ16, zWrite16, writeMask16);

							_mm_storeu_si128(reinterpret_cast<__m128i*>(pDest), blended16);
							_mm_storeu_si128(reinterpret_cast<__m128i*>(zbuf), zBlended16);
						}

						pRunSrc += ChunkSize;
						pRunZAdjust += ChunkSize;
						pDest += ChunkSize;
						zbuf += ChunkSize;
						abuf += ChunkSize;
						remaining -= ChunkSize;
						ADJUST_POINTER(pZBuffer, zbuf);
						ADJUST_POINTER(pABuffer, abuf);
					}

					while (remaining--)
					{
						int zval = zbase - static_cast<int>(static_cast<signed char>(*pRunZAdjust++));
						if (zval < *zbuf)
						{
							WORD value = pPaletteData[*pRunSrc | pAData[*abuf]];
							if constexpr (UseTint)
								*pDest = tint | value;
							else
								*pDest = value;

							*zbuf = static_cast<WORD>(zval);
						}

						++pRunSrc;
						++pDest;
						++zbuf;
						++abuf;
						ADJUST_POINTER(pZBuffer, zbuf);
						ADJUST_POINTER(pABuffer, abuf);
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
					abuf += off;
					ADJUST_POINTER(pZBuffer, zbuf);
					ADJUST_POINTER(pABuffer, abuf);
				}
			}

			return;
		}

		// Scalar
		auto handler = [pPaletteData, pAData, tint](WORD& dest, byte srcv, int zbase, WORD& zbufv, byte zadjustv, WORD abufv)
		{
			int zval = zbase - static_cast<int>(static_cast<signed char>(zadjustv));
			if (zval < zbufv)
			{
				WORD value = pPaletteData[srcv | pAData[abufv]];
				if constexpr (UseTint)
					dest = tint | value;
				else
					dest = value;
				zbufv = static_cast<WORD>(zval);
			}
		};

		RLE_PROCESS_PIXEL_DATAS(true, true, pDest, src, len, zbase, zbuf, abuf, zadjust, handler);
	}
	WORD* PaletteData;
	AlphaLightingRemapClass* AlphaRemapper;
};
