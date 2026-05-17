#pragma once

class Simd
{
public:
	enum class Level : int
	{
		Vanilla = -1,
		Scalar = 0,
		SSE2,
		AVX2,
		AVX512
	};

private:
	static Level CurrentLevel;
	static bool Initialized;

public:
	static void Initialize(Level maxLevel = Level::AVX512);
	static Level GetCurrentLevel()
	{
		return Simd::CurrentLevel;
	}

	static const char* GetLevelName(Level level);
	static Level ParseLevel(const char* pValue, Level defaultLevel);

private:
	static Level DetectBestLevel();
	static Level ClampLevel(Level level, Level maxLevel);
};
