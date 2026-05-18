#pragma once

#include "Blitter.h"

DEFINE_BLITTER(BlitTransZRemapXlatZRead, BlitterPixelWordOnly)
{
public:
	inline explicit BlitTransZRemapXlatZRead(byte** remapData, WORD* data) noexcept
	{
		this->RemapData = remapData;
		this->PaletteData = data;
	}

	virtual ~BlitTransZRemapXlatZRead() override final = default;

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
		byte** ppRemapData = this->RemapData;
		WORD* pPaletteData = this->PaletteData;

		// Scalar
		while (len--)
		{
			WORD zbufv = *zbuf++;
			byte idx = *src++;
			if (zval < zbufv && idx)
				*pDest = pPaletteData[(*ppRemapData)[idx]];
			++pDest;

			ADJUST_POINTER(ZBuffer::Instance, zbuf);
		}
	}
	byte** RemapData;
	WORD* PaletteData;
};
