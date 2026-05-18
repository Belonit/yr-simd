#pragma once

#include "RLEBlitTransLucent25AlphaZRead.h"

template<BlitterPixelWordOnly T, Simd::Level Level>
class RLEBlitTransLucent25AlphaZReadFix final : public RLEBlitTransLucent25AlphaZRead<T, Level>
{
public:
	inline explicit RLEBlitTransLucent25AlphaZReadFix(WORD* data, WORD mask, int shadecount) noexcept
		: RLEBlitTransLucent25AlphaZRead<T, Level>(data, mask, shadecount)
	{
	}

	virtual ~RLEBlitTransLucent25AlphaZReadFix() override final = default;

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
		constexpr unsigned int RGB565BlendMask = 0xF7DEu;

		WORD* pDest = reinterpret_cast<WORD*>(dst);
		WORD* pAData = LOOKUP_ALPHA_REMAPPER(alvl, this->AlphaRemapper);
		WORD* pPaletteData = this->PaletteData;

		RLE_PROCESS_PRE_LINES(true, true, pDest, src, len, line, zbuf, abuf);

		// AVX512

		// Scalar
		auto handler = [pPaletteData, pAData](WORD& dest, byte srcv, int zbase, WORD zbufv, byte zadjustv, WORD abufv)
		{
			int zval = zbase - static_cast<int>(static_cast<signed char>(zadjustv));
			if (zval < zbufv)
			{
				const unsigned int srcColor = pPaletteData[srcv | pAData[abufv]];
				const unsigned int destColor = static_cast<WORD>(dest);
				const unsigned int blendedColor = (((srcColor ^ destColor) & RGB565BlendMask) >> 1) + (srcColor & destColor);
				const unsigned int refinedColor = (srcColor | blendedColor) - (((srcColor ^ blendedColor) & RGB565BlendMask) >> 1);
				dest = static_cast<T>(refinedColor);
			}
		};

		RLE_PROCESS_PIXEL_DATAS(true, true, pDest, src, len, zbase, zbuf, abuf, zadjust, handler);
	}


};

static_assert(sizeof(RLEBlitTransLucent25AlphaZReadFix<WORD, Simd::Level::Scalar>) == sizeof(RLEBlitTransLucent25AlphaZRead<WORD, Simd::Level::Scalar>));
