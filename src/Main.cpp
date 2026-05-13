#include "Main.h"

#include <Utilities/Debug.h>
#include <Utilities/Patch.h>

HANDLE Main::hInstance = nullptr;
std::unique_ptr<MainConfig> Main::Config = std::make_unique<MainConfig>();

void Main::ExeRun()
{
	Patch::ApplyStatic();
#ifdef DEBUG
	Main::DetachFromDebugger();
#endif
}

void Main::CmdLineParse(char** ppArgs, int nNumArgs)
{
	Debug::Log("Initialized " PRODUCT_NAME " " PRODUCT_VERSION "\n");
}
