#pragma once

#include "Blitter.h"

DEFINE_BLITTER(BlitTransLucent50ZReadWrite, BlitterPixelWordOnly)
{
public:
	inline explicit BlitTransLucent50ZReadWrite(WORD* data, WORD mask) noexcept
	{
		this->PaletteData = data;
		this->Mask = mask;
	}

	virtual ~BlitTransLucent50ZReadWrite() override final = default;

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
		WORD zWriteValue = static_cast<WORD>(zval);

		// AVX2
		if constexpr (Level == Simd::Level::AVX2 && CompileAvx2)
		{
			constexpr int ChunkSize = 8;
			constexpr uintptr_t ChunkBytes = ChunkSize * sizeof(WORD);
			ZBuffer* pZBuffer = ZBuffer::Instance;
			const uintptr_t zTailAddress = reinterpret_cast<uintptr_t>(pZBuffer->BufferTail);

			const __m256i zero32 = _mm256_setzero_si256();
			const __m256i blendMask32 = _mm256_set1_epi32(static_cast<int>(mask));
			const __m256i zvalVec32 = _mm256_set1_epi32(zval);
			const __m128i zWriteVec16 = _mm_set1_epi16(static_cast<short>(zWriteValue));

			while (len >= ChunkSize)
			{
				const uintptr_t zAddress = reinterpret_cast<uintptr_t>(zbuf);
				if (zAddress + ChunkBytes > zTailAddress)
					break;

				const __m256i srcIndex32 = Avx2_Expand8ToEpi32(src);
				const __m256i srcMask32 = _mm256_cmpgt_epi32(srcIndex32, zero32);

				__m256i zMask32 = _mm256_setzero_si256();
				if (zval < 0)
				{
					zMask32 = _mm256_set1_epi32(-1);
				}
				else if (zval <= 0xFFFF)
				{
					const __m256i zbuf32 = Avx2_Load8WordAsEpi32(zbuf);
					zMask32 = _mm256_cmpgt_epi32(zbuf32, zvalVec32);
				}

				const __m256i activeMask32 = _mm256_and_si256(srcMask32, zMask32);
				if (_mm256_movemask_epi8(activeMask32))
				{
					const __m256i srcColor32 = Avx2_GatherPaletteWord(srcIndex32, pPaletteData);
					const __m256i dest32 = Avx2_Load8WordAsEpi32(pDest);

					const __m256i destHalf32 = _mm256_and_si256(_mm256_srli_epi32(dest32, 1), blendMask32);
					const __m256i srcHalf32 = _mm256_and_si256(_mm256_srli_epi32(srcColor32, 1), blendMask32);
					const __m256i result32 = _mm256_add_epi32(destHalf32, srcHalf32);

					const __m128i result16 = Avx2_PackU32ToU16(result32);
					const __m128i writeMask16 = Avx2_PackMask32ToI16(activeMask32);
					const __m128i oldValue16 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(pDest));
					const __m128i blended16 = Avx2_BlendU16(oldValue16, result16, writeMask16);
					const __m128i oldZ16 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(zbuf));
					const __m128i zWrite16 = Avx2_BlendU16(oldZ16, zWriteVec16, writeMask16);

					_mm_storeu_si128(reinterpret_cast<__m128i*>(pDest), blended16);
					_mm_storeu_si128(reinterpret_cast<__m128i*>(zbuf), zWrite16);
				}

				src += ChunkSize;
				pDest += ChunkSize;
				zbuf += ChunkSize;
				len -= ChunkSize;
				ADJUST_POINTER(pZBuffer, zbuf);
			}
		}

		// Scalar
		while (len--)
		{
			WORD& zbufv = *zbuf++;
			if (zval < zbufv)
			{
				if (byte idx = *src)
				{
					*pDest = (mask & (*pDest >> 1)) + (mask & (pPaletteData[idx] >> 1));
					zbufv = zWriteValue;
				}
			}
			++src;
			++pDest;

			ADJUST_POINTER(ZBuffer::Instance, zbuf);
		}
	}
	WORD* PaletteData;
	WORD Mask;
};
