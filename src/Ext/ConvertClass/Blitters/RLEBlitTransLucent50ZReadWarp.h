#pragma once

#include "Blitter.h"

DEFINE_RLE_BLITTER(RLEBlitTransLucent50ZReadWarp, BlitterPixelWordOnly)
{
public:
	inline explicit RLEBlitTransLucent50ZReadWarp(WORD* data, WORD mask) noexcept
	{
		this->PaletteData = data;
		this->Mask = mask;
	}

	virtual ~RLEBlitTransLucent50ZReadWarp() override final = default;

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
		WORD* pDest = reinterpret_cast<WORD*>(dst);
		WORD* pPaletteData = this->PaletteData;
		WORD mask = this->Mask;

		RLE_PROCESS_PRE_LINES(true, false, pDest, src, len, line, zbuf, abuf);

		// AVX2
		if constexpr (Level == Simd::Level::AVX2 && CompileAvx2)
		{
			if (warp >= 0)
			{
				constexpr int ChunkSize = 8;
				constexpr uintptr_t ChunkBytes = ChunkSize * sizeof(WORD);
				ZBuffer* pZBuffer = ZBuffer::Instance;
				const uintptr_t zTailAddress = reinterpret_cast<uintptr_t>(pZBuffer->BufferTail);
				const __m256i zbaseVec32 = _mm256_set1_epi32(zbase);
				const __m256i blendMask32 = _mm256_set1_epi32(static_cast<int>(mask));

				while (len > 0)
				{
					byte srcv = *src++;
					if (srcv)
					{
						byte* pRunSrc = src - 1;
						byte* pRunZAdjust = zadjust;
						int runLen = 1;
						while (runLen < len && pRunSrc[runLen])
						{
							++runLen;
						}

						int remaining = runLen;
						while (remaining >= ChunkSize)
						{
							const uintptr_t zAddress = reinterpret_cast<uintptr_t>(zbuf);
							if (zAddress + ChunkBytes > zTailAddress)
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
								const __m256i srcColors = Avx2_GatherPaletteWord(srcIndices, pPaletteData);
								const __m256i warpColors = Avx2_Load8WordAsEpi32(pDest + warp);
								const __m256i warpHalf32 = _mm256_and_si256(_mm256_srli_epi32(warpColors, 1), blendMask32);
								const __m256i srcHalf32 = _mm256_and_si256(_mm256_srli_epi32(srcColors, 1), blendMask32);
								const __m256i result32 = _mm256_add_epi32(warpHalf32, srcHalf32);
								const __m128i result16 = Avx2_PackU32ToU16(result32);
								const __m128i writeMask16 = Avx2_PackMask32ToI16(zMask32);
								const __m128i oldValue16 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(pDest));
								const __m128i blended16 = Avx2_BlendU16(oldValue16, result16, writeMask16);
								_mm_storeu_si128(reinterpret_cast<__m128i*>(pDest), blended16);
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
								*pDest = (mask & (pDest[warp] >> 1)) + (mask & (pPaletteData[*pRunSrc] >> 1));
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
		}

		// Scalar
		auto handler = [pPaletteData, mask, warp](WORD& dest, byte srcv, int zbase, WORD zbufv, byte zadjustv)
		{
			int zval = zbase - static_cast<int>(static_cast<signed char>(zadjustv));
			if (zval < zbufv)
				dest = (mask & ((&dest)[warp] >> 1)) + (mask & (pPaletteData[srcv] >> 1));
		};

		RLE_PROCESS_PIXEL_DATAS(true, false, pDest, src, len, zbase, zbuf, abuf, zadjust, handler);
	}
	WORD* PaletteData;
	WORD Mask;
};
