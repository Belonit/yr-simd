#pragma once

#include "BlitterPack.h"
#include <Utilities/Debug.h>

class NOVTABLE BlitterPack8SSE2 final
{
public:
	BlitPlainXlat<BYTE, Simd::Level::Scalar> BlitterPlainXlat;
	BlitTransXlat<BYTE, Simd::Level::Scalar> BlitterTransXlat;
	BlitTransRemapDest<BYTE, Simd::Level::Scalar> BlitterTransRemapDest;
	BlitTransZRemapXlat<BYTE, Simd::Level::Scalar> BlitterTransZRemapXlat;
	BlitTransRemapXlat<BYTE, Simd::Level::Scalar> BlitterTransRemapXlat75;
	BlitTransRemapXlat<BYTE, Simd::Level::Scalar> BlitterTransRemapXlat50;
	BlitTransRemapXlat<BYTE, Simd::Level::Scalar> BlitterTransRemapXlat25;

	RLEBlitTransXlat<BYTE, Simd::Level::Scalar> RleBlitterTransXlat;
	RLEBlitTransRemapDest<BYTE, Simd::Level::Scalar> RleBlitterTransRemapDest;
	RLEBlitTransZRemapXlat<BYTE, Simd::Level::Scalar> RleBlitterTransZRemapXlat;
	RLEBlitTransRemapXlat<BYTE, Simd::Level::Scalar> RleBlitterTransRemapXlat75;
	RLEBlitTransRemapXlat<BYTE, Simd::Level::Scalar> RleBlitterTransRemapXlat50;
	RLEBlitTransRemapXlat<BYTE, Simd::Level::Scalar> RleBlitterTransRemapXlat25;
	RLEBlitTransXlatZRead<BYTE, Simd::Level::SSE2> RleBlitterTransXlatZRead;
	RLEBlitTransRemapDestZRead<BYTE, Simd::Level::SSE2> RleBlitterTransRemapDestZRead;
	RLEBlitTransZRemapXlatZRead<BYTE, Simd::Level::SSE2> RleBlitterTransZRemapXlatZRead;
	RLEBlitTransRemapXlatZRead<BYTE, Simd::Level::SSE2> RleBlitterTransRemapXlatZRead75;
	RLEBlitTransRemapXlatZRead<BYTE, Simd::Level::SSE2> RleBlitterTransRemapXlatZRead50;
	RLEBlitTransRemapXlatZRead<BYTE, Simd::Level::SSE2> RleBlitterTransRemapXlatZRead25;
	RLEBlitTransXlatZReadWrite<BYTE, Simd::Level::SSE2> RleBlitterTransXlatZReadWrite;
	RLEBlitTransRemapDestZReadWrite<BYTE, Simd::Level::SSE2> RleBlitterTransRemapDestZReadWrite;
	RLEBlitTransZRemapXlatZReadWrite<BYTE, Simd::Level::SSE2> RleBlitterTransZRemapXlatZReadWrite;
	RLEBlitTransRemapXlatZReadWrite<BYTE, Simd::Level::SSE2> RleBlitterTransRemapXlatZReadWrite75;
	RLEBlitTransRemapXlatZReadWrite<BYTE, Simd::Level::SSE2> RleBlitterTransRemapXlatZReadWrite50;
	RLEBlitTransRemapXlatZReadWrite<BYTE, Simd::Level::SSE2> RleBlitterTransRemapXlatZReadWrite25;

public:
	inline BlitterPack8SSE2(BYTE* paletteData, BYTE* remapData, BYTE** currentZRemap)
		: BlitterPlainXlat(paletteData)
		, BlitterTransXlat(paletteData)
		, BlitterTransRemapDest(remapData)
		, BlitterTransZRemapXlat(currentZRemap, paletteData)
		, BlitterTransRemapXlat75(remapData, paletteData)
		, BlitterTransRemapXlat50(remapData, paletteData)
		, BlitterTransRemapXlat25(remapData, paletteData)
		, RleBlitterTransXlat(paletteData)
		, RleBlitterTransRemapDest(remapData)
		, RleBlitterTransZRemapXlat(currentZRemap, paletteData)
		, RleBlitterTransRemapXlat75(remapData, paletteData)
		, RleBlitterTransRemapXlat50(remapData, paletteData)
		, RleBlitterTransRemapXlat25(remapData, paletteData)
		, RleBlitterTransXlatZRead(paletteData)
		, RleBlitterTransRemapDestZRead(remapData)
		, RleBlitterTransZRemapXlatZRead(currentZRemap, paletteData)
		, RleBlitterTransRemapXlatZRead75(remapData, paletteData)
		, RleBlitterTransRemapXlatZRead50(remapData, paletteData)
		, RleBlitterTransRemapXlatZRead25(remapData, paletteData)
		, RleBlitterTransXlatZReadWrite(paletteData)
		, RleBlitterTransRemapDestZReadWrite(remapData)
		, RleBlitterTransZRemapXlatZReadWrite(currentZRemap, paletteData)
		, RleBlitterTransRemapXlatZReadWrite75(remapData, paletteData)
		, RleBlitterTransRemapXlatZReadWrite50(remapData, paletteData)
		, RleBlitterTransRemapXlatZReadWrite25(remapData, paletteData)
	{}
};
