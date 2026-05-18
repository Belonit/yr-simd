#pragma once

#include "Blitter.h"

DEFINE_BLITTER(BlitTranslucent50ZeroAlpha, BlitterPixelWordOnly)
{
public:
	inline explicit BlitTranslucent50ZeroAlpha(WORD* data, WORD mask) noexcept
	{
		this->PaletteData = data;
		this->Mask = mask;
	}

	virtual ~BlitTranslucent50ZeroAlpha() override final = default;

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
			constexpr uintptr_t ChunkBytes = ChunkSize * sizeof(WORD);
			ABuffer* pABuffer = ABuffer::Instance;
			const uintptr_t aTailAddress = reinterpret_cast<uintptr_t>(pABuffer->BufferTail);

			const __m256i zero32 = _mm256_setzero_si256();
			const __m256i blendMask32 = _mm256_set1_epi32(static_cast<int>(mask));

			while (len >= ChunkSize)
			{
				const uintptr_t aAddress = reinterpret_cast<uintptr_t>(abuf);
				if (aAddress + ChunkBytes > aTailAddress)
				{
					break;
				}

				const __m256i srcIndices = Avx2_Expand8ToEpi32(src);
				const __m256i srcMask32 = _mm256_cmpgt_epi32(srcIndices, zero32);
				const __m256i alphaValues = Avx2_Load8WordAsEpi32(abuf);
				const __m256i alphaMask32 = _mm256_cmpeq_epi32(alphaValues, zero32);
				const __m256i activeMask32 = _mm256_and_si256(srcMask32, alphaMask32);

				if (_mm256_movemask_epi8(activeMask32))
				{
					const __m256i srcColors = Avx2_GatherPaletteWord(srcIndices, pPaletteData);
					const __m256i dest32 = Avx2_Load8WordAsEpi32(pDest);
					const __m256i destHalf32 = _mm256_and_si256(_mm256_srli_epi32(dest32, 1), blendMask32);
					const __m256i srcHalf32 = _mm256_and_si256(_mm256_srli_epi32(srcColors, 1), blendMask32);
					const __m256i result32 = _mm256_add_epi32(destHalf32, srcHalf32);
					const __m128i result16 = Avx2_PackU32ToU16(result32);
					const __m128i writeMask16 = Avx2_PackMask32ToI16(activeMask32);
					const __m128i oldValue16 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(pDest));
					const __m128i blended16 = Avx2_BlendU16(oldValue16, result16, writeMask16);
					_mm_storeu_si128(reinterpret_cast<__m128i*>(pDest), blended16);
				}

				src += ChunkSize;
				pDest += ChunkSize;
				abuf += ChunkSize;
				len -= ChunkSize;
				ADJUST_POINTER(pABuffer, abuf);
			}
		}

		// Scalar
		while (len--)
		{
			if (byte idx = *src++)
			{
				if (!*abuf)
					*pDest = (mask & (*pDest >> 1)) + (mask & (pPaletteData[idx] >> 1));
			}
			++abuf;
			++pDest;

			ADJUST_POINTER(ABuffer::Instance, abuf);
		}
	}
	WORD* PaletteData;
	WORD Mask;
};
