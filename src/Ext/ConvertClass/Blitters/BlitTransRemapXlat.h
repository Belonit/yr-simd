#pragma once

#include "Blitter.h"

DEFINE_BLITTER(BlitTransRemapXlat, BlitterPixelByteOnly)
{
public:
	inline explicit BlitTransRemapXlat(BYTE* remap, BYTE* palette) noexcept
	{
		this->RemapData = remap;
		this->PaletteData = palette;
	}

	virtual ~BlitTransRemapXlat() override final = default;

	virtual void Blit_Copy(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp) override final
	{
		Blit_Impl(dst, src, len, zval, zbuf, abuf, alvl, warp);
	}

	virtual void Blit_Copy_Tinted(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp, WORD tint) override final
	{
		Blit_Impl(dst, src, len, zval, zbuf, abuf, alvl, warp);
	}

	virtual void Blit_Move(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp) override final
	{
		Blit_Impl(dst, src, len, zval, zbuf, abuf, alvl, warp);
	}

	virtual void Blit_Move_Tinted(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp, WORD tint) override final
	{
		Blit_Impl(dst, src, len, zval, zbuf, abuf, alvl, warp);
	}

private:
	__forceinline void Blit_Impl(void* dst, byte* src, int len, int zval, WORD* zbuf, WORD* abuf, int alvl, int warp)
	{
		if (len < 0)
			return;

		BYTE* pDest = reinterpret_cast<BYTE*>(dst);
		const BYTE* pPaletteData = this->PaletteData;
		const BYTE* pRemapData = this->RemapData;

		// Scalar
		while (len--)
		{
			if (BYTE idx = *src++)
				*pDest = pPaletteData[pRemapData[idx]];
			++pDest;
		}
	}
	const BYTE* RemapData;
	const BYTE* PaletteData;
};
