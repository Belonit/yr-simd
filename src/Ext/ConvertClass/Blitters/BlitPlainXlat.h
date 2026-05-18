#pragma once

#include "Blitter.h"

DEFINE_BLITTER(BlitPlainXlat, BlitterPixelByteAndWord)
{
public:
	inline explicit BlitPlainXlat(T* data) noexcept
	{
		this->PaletteData = data;
	}

	virtual ~BlitPlainXlat() override final = default;

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

		T* pDest = reinterpret_cast<T*>(dst);
		T* pPaletteData = this->PaletteData;

		// AVX2
		if constexpr (Level == Simd::Level::AVX2 && std::is_same_v<T, WORD> && CompileAvx2)
		{
			constexpr int ChunkSize = 8;

			while (len >= ChunkSize)
			{
				const __m256i srcIndex32 = Avx2_Expand8ToEpi32(src);
				const __m256i srcColor32 = Avx2_GatherPaletteWord(srcIndex32, pPaletteData);
				const __m128i result16 = Avx2_PackU32ToU16(srcColor32);

				_mm_storeu_si128(reinterpret_cast<__m128i*>(pDest), result16);

				src += ChunkSize;
				pDest += ChunkSize;
				len -= ChunkSize;
			}
		}

		// Scalar
		while (len--)
		{
			*pDest++ = pPaletteData[*src++];
		}
	}
	T* PaletteData;
};
