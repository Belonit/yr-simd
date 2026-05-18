#pragma once

#include "Blitter.h"

DEFINE_BLITTER(BlitTransLucent50AlphaZReadWarp, BlitterPixelWordOnly)
{
public:
	inline explicit BlitTransLucent50AlphaZReadWarp(WORD* data, WORD mask, int shadecount) noexcept
	{
		this->PaletteData = data;
		this->Mask = mask;
		this->AlphaRemapper = AlphaLightingRemapClass::FindOrAllocate(shadecount);
	}

	virtual ~BlitTransLucent50AlphaZReadWarp() override final = default;

	virtual void Blit_Copy(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp)
	{
		Blit_Impl(dst, src, len, zval, zbuf, abuf, alvl, warp);
	}

	virtual void Blit_Copy_Tinted(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp, WORD tint)
	{
		Blit_Impl(dst, src, len, zval, zbuf, abuf, alvl, 0);
	}

	virtual void Blit_Move(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp)
	{
		Blit_Impl(dst, src, len, zval, zbuf, abuf, alvl, 0);
	}

	virtual void Blit_Move_Tinted(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp, WORD tint)
	{
		Blit_Impl(dst, src, len, zval, zbuf, abuf, alvl, 0);
	}

private:
	__forceinline void Blit_Impl(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp)
	{
		if (len < 0)
			return;

		WORD* pDest = reinterpret_cast<WORD*>(dst);
		WORD* pAData = LOOKUP_ALPHA_REMAPPER(alvl, this->AlphaRemapper);
		WORD* pPaletteData = this->PaletteData;
		WORD mask = this->Mask;

		// AVX2
		if constexpr (Level == Simd::Level::AVX2 && CompileAvx2)
		{
			constexpr int ChunkSize = 8;
			constexpr uintptr_t ChunkBytes = ChunkSize * sizeof(WORD);
			ZBuffer* pZBuffer = ZBuffer::Instance;
			ABuffer* pABuffer = ABuffer::Instance;
			const uintptr_t zTailAddress = reinterpret_cast<uintptr_t>(pZBuffer->BufferTail);
			const uintptr_t aTailAddress = reinterpret_cast<uintptr_t>(pABuffer->BufferTail);

			const __m256i zero32 = _mm256_setzero_si256();
			const __m256i zvalVec32 = _mm256_set1_epi32(zval);
			const __m256i blendMask32 = _mm256_set1_epi32(static_cast<int>(mask));
			WORD* pWarpDest = pDest + warp;

			while (len >= ChunkSize)
			{
				const uintptr_t zAddress = reinterpret_cast<uintptr_t>(zbuf);
				const uintptr_t aAddress = reinterpret_cast<uintptr_t>(abuf);
				if (zAddress + ChunkBytes > zTailAddress || aAddress + ChunkBytes > aTailAddress)
				{
					break;
				}

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

				if (_mm256_movemask_epi8(zMask32))
				{
					const __m256i srcIndex32 = Avx2_Expand8ToEpi32(src);
					const __m256i srcMask32 = _mm256_cmpgt_epi32(srcIndex32, zero32);
					const __m256i activeMask32 = _mm256_and_si256(srcMask32, zMask32);

					if (_mm256_movemask_epi8(activeMask32))
					{
						const __m256i alphaIndex32 = Avx2_Load8WordAsEpi32(abuf);
						const __m256i alphaValue32 = Avx2_GatherWordTable256(alphaIndex32, pAData);
						const __m256i paletteIndex32 = _mm256_or_si256(srcIndex32, alphaValue32);
						const __m256i srcColor32 = Avx2_GatherWordTable(paletteIndex32, pPaletteData, 0xFFFF);
						const __m256i bg32 = Avx2_Load8WordAsEpi32(pWarpDest);

						const __m256i bgHalf32 = _mm256_and_si256(_mm256_srli_epi32(bg32, 1), blendMask32);
						const __m256i srcHalf32 = _mm256_and_si256(_mm256_srli_epi32(srcColor32, 1), blendMask32);
						const __m256i result32 = _mm256_add_epi32(bgHalf32, srcHalf32);

						const __m128i result16 = Avx2_PackU32ToU16(result32);
						const __m128i writeMask16 = Avx2_PackMask32ToI16(activeMask32);
						const __m128i oldValue16 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(pDest));
						const __m128i blended16 = Avx2_BlendU16(oldValue16, result16, writeMask16);

						_mm_storeu_si128(reinterpret_cast<__m128i*>(pDest), blended16);
					}
				}

				src += ChunkSize;
				pDest += ChunkSize;
				pWarpDest += ChunkSize;
				zbuf += ChunkSize;
				abuf += ChunkSize;
				len -= ChunkSize;
				ADJUST_POINTER(pZBuffer, zbuf);
				ADJUST_POINTER(pABuffer, abuf);
			}
		}

		// Scalar
		while (len--)
		{
			WORD zbufv = *zbuf++;
			byte idx = *src++;
			if (zval < zbufv && idx)
				*pDest = (mask & (pDest[warp] >> 1)) + (mask & (pPaletteData[idx | pAData[*abuf]] >> 1));

			++pDest;
			++abuf;

			ADJUST_POINTER(ZBuffer::Instance, zbuf);
			ADJUST_POINTER(ABuffer::Instance, abuf);
		}
	}
	WORD* PaletteData;
	WORD Mask;
	AlphaLightingRemapClass* AlphaRemapper;
};
