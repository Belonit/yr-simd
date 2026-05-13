#pragma once

#include "BlitterPack.h"

class NOVTABLE BlitterPack16Scalar final
{
public:
	BlitPlainXlat<WORD, Simd::Level::Scalar> BlitterPlainXlat;
	BlitTransXlat<WORD, Simd::Level::Scalar> BlitterTransXlat;
	BlitTransDarken<WORD, Simd::Level::Scalar> BlitterTransDarken;
	BlitTransZRemapXlat<WORD, Simd::Level::Scalar> BlitterTransZRemapXlat;
	BlitTransLucent75<WORD, Simd::Level::Scalar> BlitterTransLucent75;
	BlitTransLucent50<WORD, Simd::Level::Scalar> BlitterTransLucent50;
	BlitTransLucent25<WORD, Simd::Level::Scalar> BlitterTransLucent25;
	BlitPlainXlatZRead<WORD, Simd::Level::Scalar> BlitterPlainXlatZRead;
	BlitTransXlatZRead<WORD, Simd::Level::Scalar> BlitterTransXlatZRead;
	BlitTransDarkenZRead<WORD, Simd::Level::Scalar> BlitterTransDarkenZRead;
	BlitTransZRemapXlatZRead<WORD, Simd::Level::Scalar> BlitterTransZRemapXlatZRead;
	BlitTransLucent75ZRead<WORD, Simd::Level::Scalar> BlitterTransLucent75ZRead;
	BlitTransLucent50ZRead<WORD, Simd::Level::Scalar> BlitterTransLucent50ZRead;
	BlitTransLucent25ZRead<WORD, Simd::Level::Scalar> BlitterTransLucent25ZRead;
	BlitTransLucent75ZReadWarp<WORD, Simd::Level::Scalar> BlitterTransLucent75ZReadWarp;
	BlitTransLucent50ZReadWarp<WORD, Simd::Level::Scalar> BlitterTransLucent50ZReadWarp;
	BlitTransLucent25ZReadWarp<WORD, Simd::Level::Scalar> BlitterTransLucent25ZReadWarp;
	BlitPlainXlatZReadWrite<WORD, Simd::Level::Scalar> BlitterPlainXlatZReadWrite;
	BlitTransXlatZReadWrite<WORD, Simd::Level::Scalar> BlitterTransXlatZReadWrite;
	BlitTransDarkenZReadWrite<WORD, Simd::Level::Scalar> BlitterTransDarkenZReadWrite;
	BlitTransZRemapXlatZReadWrite<WORD, Simd::Level::Scalar> BlitterTransZRemapXlatZReadWrite;
	BlitTransLucent75ZReadWrite<WORD, Simd::Level::Scalar> BlitterTransLucent75ZReadWrite;
	BlitTransLucent50ZReadWrite<WORD, Simd::Level::Scalar> BlitterTransLucent50ZReadWrite;
	BlitTransLucent25ZReadWrite<WORD, Simd::Level::Scalar> BlitterTransLucent25ZReadWrite;
	BlitPlainXlatAlpha<WORD, Simd::Level::Scalar> BlitterPlainXlatAlpha;
	BlitTransXlatAlpha<WORD, Simd::Level::Scalar> BlitterTransXlatAlpha;
	BlitTransZRemapXlatAlpha<WORD, Simd::Level::Scalar> BlitterTransZRemapXlatAlpha;
	BlitTransLucent75Alpha<WORD, Simd::Level::Scalar> BlitterTransLucent75Alpha;
	BlitTransLucent50Alpha<WORD, Simd::Level::Scalar> BlitterTransLucent50Alpha;
	BlitTransLucent25Alpha<WORD, Simd::Level::Scalar> BlitterTransLucent25Alpha;
	BlitTransXlatWriteAlpha<WORD, Simd::Level::Scalar> BlitterTransXlatWriteAlpha;
	BlitTransXlatMultWriteAlpha<WORD, Simd::Level::Scalar> BlitterTransXlatMultWriteAlpha;
	BlitTranslucentWriteAlpha<WORD, Simd::Level::Scalar> BlitterTranslucentWriteAlpha;
	BlitTranslucent50NonzeroAlpha<WORD, Simd::Level::Scalar> BlitterTranslucent50NonzeroAlpha;
	BlitTranslucent50ZeroAlpha<WORD, Simd::Level::Scalar> BlitterTranslucent50ZeroAlpha;
	BlitPlainXlatAlpha<WORD, Simd::Level::Scalar> BlitterPlainXlatAlphaZReadSeed;
	BlitTransXlatAlphaZRead<WORD, Simd::Level::Scalar> BlitterTransXlatAlphaZRead;
	BlitTransZRemapXlatAlphaZRead<WORD, Simd::Level::Scalar> BlitterTransZRemapXlatAlphaZRead;
	BlitTransLucent75AlphaZRead<WORD, Simd::Level::Scalar> BlitterTransLucent75AlphaZRead;
	BlitTransLucent50AlphaZRead<WORD, Simd::Level::Scalar> BlitterTransLucent50AlphaZRead;
	BlitTransLucent25AlphaZRead<WORD, Simd::Level::Scalar> BlitterTransLucent25AlphaZRead;
	BlitTransLucent75AlphaZReadWarp<WORD, Simd::Level::Scalar> BlitterTransLucent75AlphaZReadWarp;
	BlitTransLucent50AlphaZReadWarp<WORD, Simd::Level::Scalar> BlitterTransLucent50AlphaZReadWarp;
	BlitTransLucent25AlphaZReadWarp<WORD, Simd::Level::Scalar> BlitterTransLucent25AlphaZReadWarp;
	BlitPlainXlatAlpha<WORD, Simd::Level::Scalar> BlitterPlainXlatAlphaZReadWriteSeed;
	BlitTransXlatAlphaZReadWrite<WORD, Simd::Level::Scalar> BlitterTransXlatAlphaZReadWrite;
	BlitTransZRemapXlatAlphaZReadWrite<WORD, Simd::Level::Scalar> BlitterTransZRemapXlatAlphaZReadWrite;
	BlitTransLucent75AlphaZReadWrite<WORD, Simd::Level::Scalar> BlitterTransLucent75AlphaZReadWrite;
	BlitTransLucent50AlphaZReadWrite<WORD, Simd::Level::Scalar> BlitterTransLucent50AlphaZReadWrite;
	BlitTransLucent25AlphaZReadWrite<WORD, Simd::Level::Scalar> BlitterTransLucent25AlphaZReadWrite;

	RLEBlitTransXlat<WORD, Simd::Level::Scalar> RleBlitterTransXlat;
	RLEBlitTransDarken<WORD, Simd::Level::Scalar> RleBlitterTransDarken;
	RLEBlitTransZRemapXlat<WORD, Simd::Level::Scalar> RleBlitterTransZRemapXlat;
	RLEBlitTransLucent75<WORD, Simd::Level::Scalar> RleBlitterTransLucent75;
	RLEBlitTransLucent50<WORD, Simd::Level::Scalar> RleBlitterTransLucent50;
	RLEBlitTransLucent25<WORD, Simd::Level::Scalar> RleBlitterTransLucent25;
	RLEBlitTransXlatZRead<WORD, Simd::Level::Scalar> RleBlitterTransXlatZRead;
	RLEBlitTransZRemapXlatZRead<WORD, Simd::Level::Scalar> RleBlitterTransZRemapXlatZRead;
	RLEBlitTransDarkenZRead<WORD, Simd::Level::Scalar> RleBlitterTransDarkenZRead;
	RLEBlitTransLucent75ZRead<WORD, Simd::Level::Scalar> RleBlitterTransLucent75ZRead;
	RLEBlitTransLucent50ZRead<WORD, Simd::Level::Scalar> RleBlitterTransLucent50ZRead;
	RLEBlitTransLucent25ZRead<WORD, Simd::Level::Scalar> RleBlitterTransLucent25ZRead;
	RLEBlitTransLucent75ZReadWarp<WORD, Simd::Level::Scalar> RleBlitterTransLucent75ZReadWarp;
	RLEBlitTransLucent50ZReadWarp<WORD, Simd::Level::Scalar> RleBlitterTransLucent50ZReadWarp;
	RLEBlitTransLucent25ZReadWarp<WORD, Simd::Level::Scalar> RleBlitterTransLucent25ZReadWarp;
	RLEBlitTransXlatZReadWrite<WORD, Simd::Level::Scalar> RleBlitterTransXlatZReadWrite;
	RLEBlitTransZRemapXlatZReadWrite<WORD, Simd::Level::Scalar> RleBlitterTransZRemapXlatZReadWrite;
	RLEBlitTransDarkenZReadWrite<WORD, Simd::Level::Scalar> RleBlitterTransDarkenZReadWrite;
	RLEBlitTransLucent75ZReadWrite<WORD, Simd::Level::Scalar> RleBlitterTransLucent75ZReadWrite;
	RLEBlitTransLucent50ZReadWrite<WORD, Simd::Level::Scalar> RleBlitterTransLucent50ZReadWrite;
	RLEBlitTransLucent25ZReadWrite<WORD, Simd::Level::Scalar> RleBlitterTransLucent25ZReadWrite;
	RLEBlitTransXlatAlpha<WORD, Simd::Level::Scalar> RleBlitterTransXlatAlpha;
	RLEBlitTransZRemapXlatAlpha<WORD, Simd::Level::Scalar> RleBlitterTransZRemapXlatAlpha;
	RLEBlitTransLucent75Alpha<WORD, Simd::Level::Scalar> RleBlitterTransLucent75Alpha;
	RLEBlitTransLucent50Alpha<WORD, Simd::Level::Scalar> RleBlitterTransLucent50Alpha;
	RLEBlitTransLucent25Alpha<WORD, Simd::Level::Scalar> RleBlitterTransLucent25Alpha;
	RLEBlitTransXlatAlphaZRead<WORD, Simd::Level::Scalar> RleBlitterTransXlatAlphaZRead;
	RLEBlitTransZRemapXlatAlphaZRead<WORD, Simd::Level::Scalar> RleBlitterTransZRemapXlatAlphaZRead;
	RLEBlitTransLucent75AlphaZRead<WORD, Simd::Level::Scalar> RleBlitterTransLucent75AlphaZRead;
	RLEBlitTransLucent50AlphaZRead<WORD, Simd::Level::Scalar> RleBlitterTransLucent50AlphaZRead;
	RLEBlitTransLucent25AlphaZRead<WORD, Simd::Level::Scalar> RleBlitterTransLucent25AlphaZRead;
	RLEBlitTransLucent75AlphaZReadWarp<WORD, Simd::Level::Scalar> RleBlitterTransLucent75AlphaZReadWarp;
	RLEBlitTransLucent50AlphaZReadWarp<WORD, Simd::Level::Scalar> RleBlitterTransLucent50AlphaZReadWarp;
	RLEBlitTransLucent25AlphaZReadWarp<WORD, Simd::Level::Scalar> RleBlitterTransLucent25AlphaZReadWarp;
	RLEBlitTransXlatAlphaZReadWrite<WORD, Simd::Level::Scalar> RleBlitterTransXlatAlphaZReadWrite;
	RLEBlitTransZRemapXlatAlphaZReadWrite<WORD, Simd::Level::Scalar> RleBlitterTransZRemapXlatAlphaZReadWrite;
	RLEBlitTransLucent75AlphaZReadWrite<WORD, Simd::Level::Scalar> RleBlitterTransLucent75AlphaZReadWrite;
	RLEBlitTransLucent50AlphaZReadWrite<WORD, Simd::Level::Scalar> RleBlitterTransLucent50AlphaZReadWrite;
	RLEBlitTransLucent25AlphaZReadWrite<WORD, Simd::Level::Scalar> RleBlitterTransLucent25AlphaZReadWrite;

	RLEBlitTransLucent75AlphaZReadFix<WORD, Simd::Level::Scalar> RleBlitterTransLucent75AlphaZReadFix;
	RLEBlitTransLucent50AlphaZReadFix<WORD, Simd::Level::Scalar> RleBlitterTransLucent50AlphaZReadFix;
	RLEBlitTransLucent25AlphaZReadFix<WORD, Simd::Level::Scalar> RleBlitterTransLucent25AlphaZReadFix;

public:
	inline BlitterPack16Scalar(WORD* paletteData, WORD* fullColorData, BYTE** currentZRemap, WORD halfTranslucencyMask, WORD quatTranslucencyMask, int shadeCount)
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
