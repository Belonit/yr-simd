#pragma once

#include "Blitter.h"

DEFINE_BLITTER(BlitTransLucent75, BlitterPixelWordOnly)
{
public:
	inline explicit BlitTransLucent75(WORD* data, WORD mask) noexcept
	{
		this->PaletteData = data;
		this->Mask = mask;
	}

	virtual ~BlitTransLucent75() override final = default;

	virtual void Blit_Copy(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp)
	{
		Blit_Impl(dst, src, len, zval, zbuf, abuf, alvl, warp);
	}

	virtual void Blit_Copy_Tinted(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp, WORD tint)
	{
		Blit_Impl(dst, src, len, zval, zbuf, abuf, alvl, warp);
	}

	virtual void Blit_Move(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp)
	{
		Blit_Impl(dst, src, len, zval, zbuf, abuf, alvl, warp);
	}

	virtual void Blit_Move_Tinted(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp, WORD tint)
	{
		Blit_Impl(dst, src, len, zval, zbuf, abuf, alvl, warp);
	}

private:
	__forceinline void Blit_Impl(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp)
	{
		if (len < 0)
			return;

		WORD* pDest = reinterpret_cast<WORD*>(dst);
		WORD* pPaletteData = this->PaletteData;
		WORD mask = this->Mask;

		// AVX2
		if constexpr (Level == Simd::Level::AVX2 && CompileAvx2)
		{
			constexpr int ChunkSize = 8;
			const __m256i zero32 = _mm256_setzero_si256();
			const __m256i blendMask32 = _mm256_set1_epi32(static_cast<int>(mask));

			while (len >= ChunkSize)
			{
				const __m256i srcIndex32 = Avx2_Expand8ToEpi32(src);
				const __m256i activeMask32 = _mm256_cmpgt_epi32(srcIndex32, zero32);
				if (_mm256_movemask_epi8(activeMask32))
				{
					const __m256i srcColor32 = Avx2_GatherPaletteWord(srcIndex32, pPaletteData);
					const __m256i dest32 = Avx2_Load8WordAsEpi32(pDest);

					const __m256i destQuarter32 = _mm256_and_si256(_mm256_srli_epi32(dest32, 2), blendMask32);
					const __m256i srcQuarter32 = _mm256_and_si256(_mm256_srli_epi32(srcColor32, 2), blendMask32);
					const __m256i result32 = _mm256_add_epi32(_mm256_add_epi32(_mm256_add_epi32(destQuarter32, destQuarter32), destQuarter32), srcQuarter32);

					const __m128i result16 = Avx2_PackU32ToU16(result32);
					const __m128i writeMask16 = Avx2_PackMask32ToI16(activeMask32);
					const __m128i oldValue16 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(pDest));
					const __m128i blended16 = Avx2_BlendU16(oldValue16, result16, writeMask16);

					_mm_storeu_si128(reinterpret_cast<__m128i*>(pDest), blended16);
				}

				src += ChunkSize;
				pDest += ChunkSize;
				len -= ChunkSize;
			}
		}

		// Scalar
		while (len--)
		{
			if (byte idx = *src++)
				*pDest = 3 * (mask & (*pDest >> 2)) + (mask & (pPaletteData[idx] >> 2));
			++pDest;
		}
	}
	WORD* PaletteData;
	WORD Mask;
};
