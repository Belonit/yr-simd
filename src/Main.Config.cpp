#include <CCINIClass.h>
#include <GameStrings.h>
#include <Helpers/Macro.h>
#include <Utilities/Debug.h>
#include <Utilities/Macro.h>
#include <Utilities/Patch.h>
#include <Utilities/Simd.h>
#include <Ext/ConvertClass/Body.h>

#include "Main.Config.h"
#include "Main.h"

_GET_FUNCTION_ADDRESS(ConvertClassExt::AllocBlitters, GetConvertClassExtAllocBlittersAddress)
_GET_FUNCTION_ADDRESS(ConvertClassExt::DeallocBlitters, GetConvertClassExtDeallocBlittersAddress)

void MainConfig::LoadFromINIFile()
{
	auto pINI = &CCINIClass::INI_RA2MD;
	if (!pINI)
		return;

	const char* const pDebugSection = "Debug";
	if (pINI->GetSection(pDebugSection))
	{
		char simdLevel[32] {};
		pINI->ReadString(pDebugSection, "MaxSimdLevel", Simd::GetLevelName(this->MaxSimdLevel), simdLevel);
		Debug::Log("Config MaxSimdLevel raw value: %s\n", simdLevel);
		this->MaxSimdLevel = Simd::ParseLevel(simdLevel, this->MaxSimdLevel);
	}
}

void MainConfig::ApplyStaticOptions()
{
	Simd::Initialize(this->MaxSimdLevel);

	if(Simd::GetCurrentLevel() > Simd::Level::Vanilla) {
		Patch::Apply_LJMP(0x48EBF0, GetConvertClassExtAllocBlittersAddress());
		Patch::Apply_LJMP(0x490490, GetConvertClassExtDeallocBlittersAddress());
	}
}

DEFINE_HOOK(0x52D21F, InitRules_ThingsThatShouldntBeSerialized, 0x6)
{
	CCINIClass* const pIniRulesMD = CCINIClass::INI_Rules;

	Main::GetConfig()->FixTransparencyBlitters = pIniRulesMD->ReadBool(GameStrings::General, "FixTransparencyBlitters", true);

	return 0;
}
