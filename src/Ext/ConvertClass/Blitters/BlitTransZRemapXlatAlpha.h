#pragma once

#include "Blitter.h"

DEFINE_BLITTER(BlitTransZRemapXlatAlpha, BlitterPixelWordOnly)
{
public:
	inline explicit BlitTransZRemapXlatAlpha(byte** remapData, WORD* data, int shadecount) noexcept
	{
		this->RemapData = remapData;
		this->PaletteData = data;
		this->AlphaRemapper = AlphaLightingRemapClass::FindOrAllocate(shadecount);
	}

	virtual ~BlitTransZRemapXlatAlpha() override final = default;

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

		WORD* pDest = reinterpret_cast<WORD*>(dst);
		byte* const* ppRemapData = this->RemapData;
		const WORD* pAData = LOOKUP_ALPHA_REMAPPER(alvl, this->AlphaRemapper);
		const WORD* pPaletteData = this->PaletteData;

		// Scalar
		while (len--)
		{
			if (byte idx = *src++)
				*pDest = pPaletteData[(*ppRemapData)[idx] | pAData[*abuf]];
			++pDest;
			++abuf;

			ADJUST_POINTER(ABuffer::Instance, abuf);
		}
	}
	byte** RemapData;
	const WORD* PaletteData;
	AlphaLightingRemapClass* AlphaRemapper;
};
