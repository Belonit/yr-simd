#pragma once

#include "Blitter.h"

DEFINE_RLE_BLITTER(RLEBlitTransZRemapXlatAlphaZRead, BlitterPixelWordOnly)
{
public:
	inline explicit RLEBlitTransZRemapXlatAlphaZRead(byte** remapData, WORD* data, int shadecount) noexcept
	{
		this->RemapData = remapData;
		this->PaletteData = data;
		this->AlphaRemapper = AlphaLightingRemapClass::FindOrAllocate(shadecount);
	}

	virtual ~RLEBlitTransZRemapXlatAlphaZRead() override final = default;

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
		byte** pRemapData = this->RemapData;
		WORD* pPaletteData = this->PaletteData;
		WORD* pAData = LOOKUP_ALPHA_REMAPPER(alvl, this->AlphaRemapper);

		RLE_PROCESS_PRE_LINES(true, true, pDest, src, len, line, zbuf, abuf);

		// Scalar
		auto handler = [pRemapData, pPaletteData, pAData](WORD& dest, byte srcv, int zbase, WORD zbufv, byte zadjustv, WORD abufv)
		{
			int zval = zbase - static_cast<int>(static_cast<signed char>(zadjustv));
			if (zval < zbufv)
				dest = pPaletteData[(*pRemapData)[srcv] | pAData[abufv]];
		};

		RLE_PROCESS_PIXEL_DATAS(true, true, pDest, src, len, zbase, zbuf, abuf, zadjust, handler);
	}
	byte** RemapData;
	WORD* PaletteData;
	AlphaLightingRemapClass* AlphaRemapper;
};
