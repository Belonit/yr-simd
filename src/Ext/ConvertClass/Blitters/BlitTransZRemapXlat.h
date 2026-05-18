#pragma once

#include "Blitter.h"

DEFINE_BLITTER(BlitTransZRemapXlat, BlitterPixelByteAndWord)
{
public:
	inline explicit BlitTransZRemapXlat(byte** remapData, T* data) noexcept
	{
		this->RemapData = remapData;
		this->PaletteData = data;
	}

	virtual ~BlitTransZRemapXlat() override final = default;

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
		byte** ppRemapData = this->RemapData;
		T* pPaletteData = this->PaletteData;

		// Scalar
		while (len--)
		{
			if (byte idx = *src++)
				*pDest = pPaletteData[(*ppRemapData)[idx]];
			++pDest;
		}
	}
	byte** RemapData;
	T* PaletteData;
};
