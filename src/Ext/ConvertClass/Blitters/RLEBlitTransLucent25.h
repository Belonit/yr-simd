#pragma once

#include "Blitter.h"

DEFINE_RLE_BLITTER(RLEBlitTransLucent25, BlitterPixelWordOnly)
{
public:
	inline explicit RLEBlitTransLucent25(WORD * data, WORD mask) noexcept
	{
		this->PaletteData = data;
		this->Mask = mask;
	}

	virtual ~RLEBlitTransLucent25() override final = default;

	virtual void Blit_Copy(void* dst, byte * src, int len, int line, int zbase, WORD * zbuf, WORD * abuf, int alvl, int warp, byte * zadjust)
	{
		Blit_Impl(dst, src, len, line, zbase, zbuf, abuf, alvl, warp, zadjust);
	}

	virtual void Blit_Copy_Tinted(void* dst, byte * src, int len, int line, int zbase, WORD * zbuf, WORD * abuf, int alvl, int warp, byte * zadjust, WORD tint)
	{
		Blit_Impl(dst, src, len, line, zbase, zbuf, abuf, alvl, warp, zadjust);
	}

private:
	__forceinline void Blit_Impl(void* dst, byte * src, int len, int line, int zbase, WORD * zbuf, WORD * abuf, int alvl, int warp, byte * zadjust)
	{
		WORD* pDest = reinterpret_cast<WORD*>(dst);
		WORD* pPaletteData = this->PaletteData;
		WORD mask = this->Mask;

		RLE_PROCESS_PRE_LINES(false, false, pDest, src, len, line, zbuf, abuf);

		// AVX2
		if constexpr (Level == Simd::Level::AVX2 && CompileAvx2)
		{
			constexpr int ChunkSize = 8;
			const __m256i blendMask32 = _mm256_set1_epi32(static_cast<int>(mask));

			while (len > 0)
			{
				byte srcv = *src++;
				if (srcv)
				{
					byte* pRunSrc = src - 1;
					int runLen = 1;
					while (runLen < len && pRunSrc[runLen])
					{
						++runLen;
					}

					int remaining = runLen;
					while (remaining >= ChunkSize)
					{
						const __m256i srcIndices = Avx2_Expand8ToEpi32(pRunSrc);
						const __m256i srcColors = Avx2_GatherPaletteWord(srcIndices, pPaletteData);
						const __m256i dest32 = Avx2_Load8WordAsEpi32(pDest);

						const __m256i destQuarter32 = _mm256_and_si256(_mm256_srli_epi32(dest32, 2), blendMask32);
						const __m256i srcQuarter32 = _mm256_and_si256(_mm256_srli_epi32(srcColors, 2), blendMask32);
						const __m256i result32 = _mm256_add_epi32(destQuarter32, _mm256_add_epi32(_mm256_add_epi32(srcQuarter32, srcQuarter32), srcQuarter32));
						const __m128i result16 = Avx2_PackU32ToU16(result32);
						_mm_storeu_si128(reinterpret_cast<__m128i*>(pDest), result16);

						pRunSrc += ChunkSize;
						pDest += ChunkSize;
						remaining -= ChunkSize;
					}

					while (remaining--)
					{
						*pDest = (mask & (*pDest >> 2)) + 3 * (mask & (pPaletteData[*pRunSrc++] >> 2));
						++pDest;
					}

					src = pRunSrc;
					len -= runLen;
				}
				else
				{
					byte off = *src++;
					len -= off;
					pDest += off;
				}
			}

			return;
		}

		// Scalar
		auto handler = [pPaletteData, mask](WORD& dest, byte srcv)
		{
			dest = (mask & (dest >> 2)) + 3 * (mask & (pPaletteData[srcv] >> 2));
		};

		RLE_PROCESS_PIXEL_DATAS(false, false, pDest, src, len, zbase, zbuf, abuf, zadjust, handler);
	}
	WORD* PaletteData;
	WORD Mask;
};
