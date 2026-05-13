#pragma once

#include <Utilities/Simd.h>

class MainConfig
{
public:
	bool FixTransparencyBlitters;
	Simd::Level MaxSimdLevel;

	MainConfig()
		: FixTransparencyBlitters { true }
		, MaxSimdLevel { Simd::Level::AVX512 }
	{}

	void LoadFromINIFile();
	void ApplyStaticOptions();
};
