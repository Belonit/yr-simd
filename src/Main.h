#pragma once
#include "version.h"
#include "Main.Config.h"
#include <Windows.h>
#include <memory>

class CCINIClass;
class AbstractClass;

class Main
{
private:
	static std::unique_ptr<MainConfig> Config;

public:
	static void ExeRun();
	static void CmdLineParse(char** ppArgs, int nNumArgs);

	static MainConfig* GetConfig()
	{
		return Config.get();
	}

	static HANDLE hInstance;

#ifdef DEBUG
	static void DetachFromDebugger();
	static bool TryDetachFromDebugger();
#endif
};
