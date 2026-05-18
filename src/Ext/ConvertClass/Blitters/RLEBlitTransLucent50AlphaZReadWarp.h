#pragma once

#include "Blitter.h"

DEFINE_RLE_BLITTER(RLEBlitTransLucent50AlphaZReadWarp, BlitterPixelWordOnly)
{
public:
	inline explicit RLEBlitTransLucent50AlphaZReadWarp(WORD* data, WORD mask, int shadecount) noexcept
	{
		this->PaletteData = data;
		this->Mask = mask;
		this->AlphaRemapper = AlphaLightingRemapClass::FindOrAllocate(shadecount);
	}

	virtual ~RLEBlitTransLucent50AlphaZReadWarp() override final = default;

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
		WORD* pAData = LOOKUP_ALPHA_REMAPPER(alvl, this->AlphaRemapper);
		WORD* pPaletteData = this->PaletteData;
		WORD mask = this->Mask;

		RLE_PROCESS_PRE_LINES(true, true, pDest, src, len, line, zbuf, abuf);

		// AVX512

		// Scalar
		auto handler = [pPaletteData, pAData, mask, warp](WORD& dest, byte srcv, int zbase, WORD zbufv, byte zadjustv, WORD abufv)
		{
			int zval = zbase - static_cast<int>(static_cast<signed char>(zadjustv));
			if (zval < zbufv)
				dest = (mask & ((&dest)[warp] >> 1)) + (mask & (pPaletteData[srcv | pAData[abufv]] >> 1));
		};

		RLE_PROCESS_PIXEL_DATAS(true, true, pDest, src, len, zbase, zbuf, abuf, zadjust, handler);
	}
	WORD* PaletteData;
	WORD Mask;
	AlphaLightingRemapClass* AlphaRemapper;
};
