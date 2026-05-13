#pragma once

#include "BlitterPack.h"

class NOVTABLE BlitterPack16SSE2 final
{
public:
	BlitPlainXlat<WORD, Simd::Level::Scalar> BlitterPlainXlat;
	BlitTransXlat<WORD, Simd::Level::Scalar> BlitterTransXlat;
	BlitTransDarken<WORD, Simd::Level::SSE2> BlitterTransDarken;
	BlitTransZRemapXlat<WORD, Simd::Level::SSE2> BlitterTransZRemapXlat;
	BlitTransLucent75<WORD, Simd::Level::SSE2> BlitterTransLucent75;
	BlitTransLucent50<WORD, Simd::Level::SSE2> BlitterTransLucent50;
	BlitTransLucent25<WORD, Simd::Level::SSE2> BlitterTransLucent25;
	BlitPlainXlatZRead<WORD, Simd::Level::SSE2> BlitterPlainXlatZRead;
	BlitTransXlatZRead<WORD, Simd::Level::SSE2> BlitterTransXlatZRead;
	BlitTransDarkenZRead<WORD, Simd::Level::SSE2> BlitterTransDarkenZRead;
	BlitTransZRemapXlatZRead<WORD, Simd::Level::SSE2> BlitterTransZRemapXlatZRead;
	BlitTransLucent75ZRead<WORD, Simd::Level::SSE2> BlitterTransLucent75ZRead;
	BlitTransLucent50ZRead<WORD, Simd::Level::SSE2> BlitterTransLucent50ZRead;
	BlitTransLucent25ZRead<WORD, Simd::Level::SSE2> BlitterTransLucent25ZRead;
	BlitTransLucent75ZReadWarp<WORD, Simd::Level::SSE2> BlitterTransLucent75ZReadWarp;
	BlitTransLucent50ZReadWarp<WORD, Simd::Level::SSE2> BlitterTransLucent50ZReadWarp;
	BlitTransLucent25ZReadWarp<WORD, Simd::Level::SSE2> BlitterTransLucent25ZReadWarp;
	BlitPlainXlatZReadWrite<WORD, Simd::Level::SSE2> BlitterPlainXlatZReadWrite;
	BlitTransXlatZReadWrite<WORD, Simd::Level::SSE2> BlitterTransXlatZReadWrite;
	BlitTransDarkenZReadWrite<WORD, Simd::Level::SSE2> BlitterTransDarkenZReadWrite;
	BlitTransZRemapXlatZReadWrite<WORD, Simd::Level::SSE2> BlitterTransZRemapXlatZReadWrite;
	BlitTransLucent75ZReadWrite<WORD, Simd::Level::SSE2> BlitterTransLucent75ZReadWrite;
	BlitTransLucent50ZReadWrite<WORD, Simd::Level::SSE2> BlitterTransLucent50ZReadWrite;
	BlitTransLucent25ZReadWrite<WORD, Simd::Level::SSE2> BlitterTransLucent25ZReadWrite;
	BlitPlainXlatAlpha<WORD, Simd::Level::Scalar> BlitterPlainXlatAlpha;
	BlitTransXlatAlpha<WORD, Simd::Level::Scalar> BlitterTransXlatAlpha;
	BlitTransZRemapXlatAlpha<WORD, Simd::Level::SSE2> BlitterTransZRemapXlatAlpha;
	BlitTransLucent75Alpha<WORD, Simd::Level::SSE2> BlitterTransLucent75Alpha;
	BlitTransLucent50Alpha<WORD, Simd::Level::SSE2> BlitterTransLucent50Alpha;
	BlitTransLucent25Alpha<WORD, Simd::Level::SSE2> BlitterTransLucent25Alpha;
	BlitTransXlatWriteAlpha<WORD, Simd::Level::Scalar> BlitterTransXlatWriteAlpha;
	BlitTransXlatMultWriteAlpha<WORD, Simd::Level::Scalar> BlitterTransXlatMultWriteAlpha;
	BlitTranslucentWriteAlpha<WORD, Simd::Level::Scalar> BlitterTranslucentWriteAlpha;
	BlitTranslucent50NonzeroAlpha<WORD, Simd::Level::SSE2> BlitterTranslucent50NonzeroAlpha;
	BlitTranslucent50ZeroAlpha<WORD, Simd::Level::SSE2> BlitterTranslucent50ZeroAlpha;
	BlitPlainXlatAlpha<WORD, Simd::Level::Scalar> BlitterPlainXlatAlphaZReadSeed;
	BlitTransXlatAlphaZRead<WORD, Simd::Level::SSE2> BlitterTransXlatAlphaZRead;
	BlitTransZRemapXlatAlphaZRead<WORD, Simd::Level::SSE2> BlitterTransZRemapXlatAlphaZRead;
	BlitTransLucent75AlphaZRead<WORD, Simd::Level::SSE2> BlitterTransLucent75AlphaZRead;
	BlitTransLucent50AlphaZRead<WORD, Simd::Level::SSE2> BlitterTransLucent50AlphaZRead;
	BlitTransLucent25AlphaZRead<WORD, Simd::Level::SSE2> BlitterTransLucent25AlphaZRead;
	BlitTransLucent75AlphaZReadWarp<WORD, Simd::Level::SSE2> BlitterTransLucent75AlphaZReadWarp;
	BlitTransLucent50AlphaZReadWarp<WORD, Simd::Level::SSE2> BlitterTransLucent50AlphaZReadWarp;
	BlitTransLucent25AlphaZReadWarp<WORD, Simd::Level::SSE2> BlitterTransLucent25AlphaZReadWarp;
	BlitPlainXlatAlpha<WORD, Simd::Level::Scalar> BlitterPlainXlatAlphaZReadWriteSeed;
	BlitTransXlatAlphaZReadWrite<WORD, Simd::Level::SSE2> BlitterTransXlatAlphaZReadWrite;
	BlitTransZRemapXlatAlphaZReadWrite<WORD, Simd::Level::SSE2> BlitterTransZRemapXlatAlphaZReadWrite;
	BlitTransLucent75AlphaZReadWrite<WORD, Simd::Level::SSE2> BlitterTransLucent75AlphaZReadWrite;
	BlitTransLucent50AlphaZReadWrite<WORD, Simd::Level::SSE2> BlitterTransLucent50AlphaZReadWrite;
	BlitTransLucent25AlphaZReadWrite<WORD, Simd::Level::SSE2> BlitterTransLucent25AlphaZReadWrite;

	RLEBlitTransXlat<WORD, Simd::Level::Scalar> RleBlitterTransXlat;
	RLEBlitTransDarken<WORD, Simd::Level::SSE2> RleBlitterTransDarken;
	RLEBlitTransZRemapXlat<WORD, Simd::Level::SSE2> RleBlitterTransZRemapXlat;
	RLEBlitTransLucent75<WORD, Simd::Level::SSE2> RleBlitterTransLucent75;
	RLEBlitTransLucent50<WORD, Simd::Level::SSE2> RleBlitterTransLucent50;
	RLEBlitTransLucent25<WORD, Simd::Level::SSE2> RleBlitterTransLucent25;
	RLEBlitTransXlatZRead<WORD, Simd::Level::SSE2> RleBlitterTransXlatZRead;
	RLEBlitTransZRemapXlatZRead<WORD, Simd::Level::SSE2> RleBlitterTransZRemapXlatZRead;
	RLEBlitTransDarkenZRead<WORD, Simd::Level::SSE2> RleBlitterTransDarkenZRead;
	RLEBlitTransLucent75ZRead<WORD, Simd::Level::SSE2> RleBlitterTransLucent75ZRead;
	RLEBlitTransLucent50ZRead<WORD, Simd::Level::SSE2> RleBlitterTransLucent50ZRead;
	RLEBlitTransLucent25ZRead<WORD, Simd::Level::SSE2> RleBlitterTransLucent25ZRead;
	RLEBlitTransLucent75ZReadWarp<WORD, Simd::Level::SSE2> RleBlitterTransLucent75ZReadWarp;
	RLEBlitTransLucent50ZReadWarp<WORD, Simd::Level::SSE2> RleBlitterTransLucent50ZReadWarp;
	RLEBlitTransLucent25ZReadWarp<WORD, Simd::Level::SSE2> RleBlitterTransLucent25ZReadWarp;
	RLEBlitTransXlatZReadWrite<WORD, Simd::Level::SSE2> RleBlitterTransXlatZReadWrite;
	RLEBlitTransZRemapXlatZReadWrite<WORD, Simd::Level::SSE2> RleBlitterTransZRemapXlatZReadWrite;
	RLEBlitTransDarkenZReadWrite<WORD, Simd::Level::SSE2> RleBlitterTransDarkenZReadWrite;
	RLEBlitTransLucent75ZReadWrite<WORD, Simd::Level::SSE2> RleBlitterTransLucent75ZReadWrite;
	RLEBlitTransLucent50ZReadWrite<WORD, Simd::Level::SSE2> RleBlitterTransLucent50ZReadWrite;
	RLEBlitTransLucent25ZReadWrite<WORD, Simd::Level::SSE2> RleBlitterTransLucent25ZReadWrite;
	RLEBlitTransXlatAlpha<WORD, Simd::Level::Scalar> RleBlitterTransXlatAlpha;
	RLEBlitTransZRemapXlatAlpha<WORD, Simd::Level::SSE2> RleBlitterTransZRemapXlatAlpha;
	RLEBlitTransLucent75Alpha<WORD, Simd::Level::SSE2> RleBlitterTransLucent75Alpha;
	RLEBlitTransLucent50Alpha<WORD, Simd::Level::SSE2> RleBlitterTransLucent50Alpha;
	RLEBlitTransLucent25Alpha<WORD, Simd::Level::SSE2> RleBlitterTransLucent25Alpha;
	RLEBlitTransXlatAlphaZRead<WORD, Simd::Level::SSE2> RleBlitterTransXlatAlphaZRead;
	RLEBlitTransZRemapXlatAlphaZRead<WORD, Simd::Level::SSE2> RleBlitterTransZRemapXlatAlphaZRead;
	RLEBlitTransLucent75AlphaZRead<WORD, Simd::Level::SSE2> RleBlitterTransLucent75AlphaZRead;
	RLEBlitTransLucent50AlphaZRead<WORD, Simd::Level::SSE2> RleBlitterTransLucent50AlphaZRead;
	RLEBlitTransLucent25AlphaZRead<WORD, Simd::Level::SSE2> RleBlitterTransLucent25AlphaZRead;
	RLEBlitTransLucent75AlphaZReadWarp<WORD, Simd::Level::SSE2> RleBlitterTransLucent75AlphaZReadWarp;
	RLEBlitTransLucent50AlphaZReadWarp<WORD, Simd::Level::SSE2> RleBlitterTransLucent50AlphaZReadWarp;
	RLEBlitTransLucent25AlphaZReadWarp<WORD, Simd::Level::SSE2> RleBlitterTransLucent25AlphaZReadWarp;
	RLEBlitTransXlatAlphaZReadWrite<WORD, Simd::Level::SSE2> RleBlitterTransXlatAlphaZReadWrite;
	RLEBlitTransZRemapXlatAlphaZReadWrite<WORD, Simd::Level::SSE2> RleBlitterTransZRemapXlatAlphaZReadWrite;
	RLEBlitTransLucent75AlphaZReadWrite<WORD, Simd::Level::SSE2> RleBlitterTransLucent75AlphaZReadWrite;
	RLEBlitTransLucent50AlphaZReadWrite<WORD, Simd::Level::SSE2> RleBlitterTransLucent50AlphaZReadWrite;
	RLEBlitTransLucent25AlphaZReadWrite<WORD, Simd::Level::SSE2> RleBlitterTransLucent25AlphaZReadWrite;

	RLEBlitTransLucent75AlphaZReadFix<WORD, Simd::Level::SSE2> RleBlitterTransLucent75AlphaZReadFix;
	RLEBlitTransLucent50AlphaZReadFix<WORD, Simd::Level::SSE2> RleBlitterTransLucent50AlphaZReadFix;
	RLEBlitTransLucent25AlphaZReadFix<WORD, Simd::Level::SSE2> RleBlitterTransLucent25AlphaZReadFix;

public:
	inline BlitterPack16SSE2::BlitterPack16SSE2(WORD* paletteData, WORD* fullColorData, BYTE** currentZRemap, WORD halfTranslucencyMask, WORD quatTranslucencyMask, int shadeCount)
		: BlitterPlainXlat(paletteData)
		, BlitterTransXlat(paletteData)
		, BlitterTransDarken(halfTranslucencyMask)
		, BlitterTransZRemapXlat(currentZRemap, paletteData)
		, BlitterTransLucent75(paletteData, quatTranslucencyMask)
		, BlitterTransLucent50(paletteData, halfTranslucencyMask)
		, BlitterTransLucent25(paletteData, quatTranslucencyMask)
		, BlitterPlainXlatZRead(paletteData)
		, BlitterTransXlatZRead(paletteData)
		, BlitterTransDarkenZRead(halfTranslucencyMask)
		, BlitterTransZRemapXlatZRead(currentZRemap, paletteData)
		, BlitterTransLucent75ZRead(paletteData, quatTranslucencyMask)
		, BlitterTransLucent50ZRead(paletteData, halfTranslucencyMask)
		, BlitterTransLucent25ZRead(paletteData, quatTranslucencyMask)
		, BlitterTransLucent75ZReadWarp(paletteData, quatTranslucencyMask)
		, BlitterTransLucent50ZReadWarp(paletteData, halfTranslucencyMask)
		, BlitterTransLucent25ZReadWarp(paletteData, quatTranslucencyMask)
		, BlitterPlainXlatZReadWrite(paletteData)
		, BlitterTransXlatZReadWrite(paletteData)
		, BlitterTransDarkenZReadWrite(halfTranslucencyMask)
		, BlitterTransZRemapXlatZReadWrite(currentZRemap, paletteData)
		, BlitterTransLucent75ZReadWrite(paletteData, quatTranslucencyMask)
		, BlitterTransLucent50ZReadWrite(paletteData, halfTranslucencyMask)
		, BlitterTransLucent25ZReadWrite(paletteData, quatTranslucencyMask)
		, BlitterPlainXlatAlpha(fullColorData, shadeCount)
		, BlitterTransXlatAlpha(fullColorData, shadeCount)
		, BlitterTransZRemapXlatAlpha(currentZRemap, fullColorData, shadeCount)
		, BlitterTransLucent75Alpha(fullColorData, quatTranslucencyMask, shadeCount)
		, BlitterTransLucent50Alpha(fullColorData, halfTranslucencyMask, shadeCount)
		, BlitterTransLucent25Alpha(fullColorData, quatTranslucencyMask, shadeCount)
		, BlitterTransXlatWriteAlpha()
		, BlitterTransXlatMultWriteAlpha()
		, BlitterTranslucentWriteAlpha(fullColorData)
		, BlitterTranslucent50NonzeroAlpha(paletteData, halfTranslucencyMask)
		, BlitterTranslucent50ZeroAlpha(paletteData, halfTranslucencyMask)
		, BlitterPlainXlatAlphaZReadSeed(fullColorData, shadeCount)
		, BlitterTransXlatAlphaZRead(fullColorData, shadeCount)
		, BlitterTransZRemapXlatAlphaZRead(currentZRemap, fullColorData, shadeCount)
		, BlitterTransLucent75AlphaZRead(fullColorData, quatTranslucencyMask, shadeCount)
		, BlitterTransLucent50AlphaZRead(fullColorData, halfTranslucencyMask, shadeCount)
		, BlitterTransLucent25AlphaZRead(fullColorData, quatTranslucencyMask, shadeCount)
		, BlitterTransLucent75AlphaZReadWarp(fullColorData, quatTranslucencyMask, shadeCount)
		, BlitterTransLucent50AlphaZReadWarp(fullColorData, halfTranslucencyMask, shadeCount)
		, BlitterTransLucent25AlphaZReadWarp(fullColorData, quatTranslucencyMask, shadeCount)
		, BlitterPlainXlatAlphaZReadWriteSeed(fullColorData, shadeCount)
		, BlitterTransXlatAlphaZReadWrite(fullColorData, shadeCount)
		, BlitterTransZRemapXlatAlphaZReadWrite(currentZRemap, fullColorData, shadeCount)
		, BlitterTransLucent75AlphaZReadWrite(fullColorData, quatTranslucencyMask, shadeCount)
		, BlitterTransLucent50AlphaZReadWrite(fullColorData, halfTranslucencyMask, shadeCount)
		, BlitterTransLucent25AlphaZReadWrite(fullColorData, quatTranslucencyMask, shadeCount)
		, RleBlitterTransXlat(paletteData)
		, RleBlitterTransDarken(halfTranslucencyMask)
		, RleBlitterTransZRemapXlat(currentZRemap, paletteData)
		, RleBlitterTransLucent75(paletteData, quatTranslucencyMask)
		, RleBlitterTransLucent50(paletteData, halfTranslucencyMask)
		, RleBlitterTransLucent25(paletteData, quatTranslucencyMask)
		, RleBlitterTransXlatZRead(paletteData)
		, RleBlitterTransZRemapXlatZRead(currentZRemap, paletteData)
		, RleBlitterTransDarkenZRead(halfTranslucencyMask)
		, RleBlitterTransLucent75ZRead(paletteData, quatTranslucencyMask)
		, RleBlitterTransLucent50ZRead(paletteData, halfTranslucencyMask)
		, RleBlitterTransLucent25ZRead(paletteData, quatTranslucencyMask)
		, RleBlitterTransLucent75ZReadWarp(paletteData, quatTranslucencyMask)
		, RleBlitterTransLucent50ZReadWarp(paletteData, halfTranslucencyMask)
		, RleBlitterTransLucent25ZReadWarp(paletteData, quatTranslucencyMask)
		, RleBlitterTransXlatZReadWrite(paletteData)
		, RleBlitterTransZRemapXlatZReadWrite(currentZRemap, paletteData)
		, RleBlitterTransDarkenZReadWrite(halfTranslucencyMask)
		, RleBlitterTransLucent75ZReadWrite(paletteData, quatTranslucencyMask)
		, RleBlitterTransLucent50ZReadWrite(paletteData, halfTranslucencyMask)
		, RleBlitterTransLucent25ZReadWrite(paletteData, quatTranslucencyMask)
		, RleBlitterTransXlatAlpha(fullColorData, shadeCount)
		, RleBlitterTransZRemapXlatAlpha(currentZRemap, fullColorData, shadeCount)
		, RleBlitterTransLucent75Alpha(fullColorData, quatTranslucencyMask, shadeCount)
		, RleBlitterTransLucent50Alpha(fullColorData, halfTranslucencyMask, shadeCount)
		, RleBlitterTransLucent25Alpha(fullColorData, quatTranslucencyMask, shadeCount)
		, RleBlitterTransXlatAlphaZRead(fullColorData, shadeCount)
		, RleBlitterTransZRemapXlatAlphaZRead(currentZRemap, fullColorData, shadeCount)
		, RleBlitterTransLucent75AlphaZRead(fullColorData, quatTranslucencyMask, shadeCount)
		, RleBlitterTransLucent50AlphaZRead(fullColorData, halfTranslucencyMask, shadeCount)
		, RleBlitterTransLucent25AlphaZRead(fullColorData, quatTranslucencyMask, shadeCount)
		, RleBlitterTransLucent75AlphaZReadWarp(fullColorData, quatTranslucencyMask, shadeCount)
		, RleBlitterTransLucent50AlphaZReadWarp(fullColorData, halfTranslucencyMask, shadeCount)
		, RleBlitterTransLucent25AlphaZReadWarp(fullColorData, quatTranslucencyMask, shadeCount)
		, RleBlitterTransXlatAlphaZReadWrite(fullColorData, shadeCount)
		, RleBlitterTransZRemapXlatAlphaZReadWrite(currentZRemap, fullColorData, shadeCount)
		, RleBlitterTransLucent75AlphaZReadWrite(fullColorData, quatTranslucencyMask, shadeCount)
		, RleBlitterTransLucent50AlphaZReadWrite(fullColorData, halfTranslucencyMask, shadeCount)
		, RleBlitterTransLucent25AlphaZReadWrite(fullColorData, quatTranslucencyMask, shadeCount)

		, RleBlitterTransLucent75AlphaZReadFix(fullColorData, quatTranslucencyMask, shadeCount)
		, RleBlitterTransLucent50AlphaZReadFix(fullColorData, halfTranslucencyMask, shadeCount)
		, RleBlitterTransLucent25AlphaZReadFix(fullColorData, quatTranslucencyMask, shadeCount)
	{}
};
