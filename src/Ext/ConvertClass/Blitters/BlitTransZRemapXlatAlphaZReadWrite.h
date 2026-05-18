#pragma once

#include "Blitter.h"

DEFINE_BLITTER(BlitTransZRemapXlatAlphaZReadWrite, BlitterPixelWordOnly)
{
public:
	inline explicit BlitTransZRemapXlatAlphaZReadWrite(byte** remapData, WORD* data, int shadecount) noexcept
	{
		this->RemapData = remapData;
		this->PaletteData = data;
		this->AlphaRemapper = AlphaLightingRemapClass::FindOrAllocate(shadecount);
	}

	virtual ~BlitTransZRemapXlatAlphaZReadWrite() override final = default;

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
		WORD* pAData = LOOKUP_ALPHA_REMAPPER(alvl, this->AlphaRemapper);
		WORD* pPaletteData = this->PaletteData;

		// Scalar
		while (len--)
		{
			WORD& zbufv = *zbuf++;
			byte idx = *src++;
			if (zval < zbufv && idx)
			{
				*pDest = pPaletteData[(*ppRemapData)[idx] | pAData[*abuf]];
				zbufv = static_cast<WORD>(zval);
			}

			++pDest;
			++abuf;

			ADJUST_POINTER(ZBuffer::Instance, zbuf);
			ADJUST_POINTER(ABuffer::Instance, abuf);
		}
	}
	byte** RemapData;
	WORD* PaletteData;
	AlphaLightingRemapClass* AlphaRemapper;
};
