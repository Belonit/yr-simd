#pragma once

#include "Blitter.h"

DEFINE_RLE_BLITTER(RLEBlitTransLucent75Alpha, BlitterPixelWordOnly)
{
public:
	inline explicit RLEBlitTransLucent75Alpha(WORD* data, WORD mask, int shadecount) noexcept
	{
		this->PaletteData = data;
		this->Mask = mask;
		this->AlphaRemapper = AlphaLightingRemapClass::FindOrAllocate(shadecount);
	}

	virtual ~RLEBlitTransLucent75Alpha() override final = default;

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

		RLE_PROCESS_PRE_LINES(false, true, pDest, src, len, line, zbuf, abuf);

		// AVX512

		// Scalar
		auto handler = [pPaletteData, pAData, mask](WORD& dest, byte srcv, WORD abufv)
		{
			dest = 3 * (mask & (dest >> 2)) + (mask & (pPaletteData[srcv | pAData[abufv]] >> 2));
		};

		RLE_PROCESS_PIXEL_DATAS(false, true, pDest, src, len, zbase, zbuf, abuf, zadjust, handler);
	}
	WORD* PaletteData;
	WORD Mask;
	AlphaLightingRemapClass* AlphaRemapper;
};
