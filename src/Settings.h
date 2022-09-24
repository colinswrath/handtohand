#pragma once
#include <SimpleIni.h>

class Settings
{
public:
	inline static float BonusXPPerLevel;
	inline static float BaseXP;

	inline static void LoadSettings()
	{
		CSimpleIniA ini;
		ini.SetUnicode();
		ini.LoadFile(R"(.\Data\SKSE\Plugins\HandToHand.ini)");

		auto bonusXP = (float)ini.GetDoubleValue("HandToHand", "fBonusXPPerLevel", 0.15);
		auto baseXP = (float)ini.GetDoubleValue("HandToHand", "fBaseXPHerHit", 3.0);

		(bonusXP < 0.0 || bonusXP > 100.0) ? BonusXPPerLevel = 0.15f : BonusXPPerLevel = bonusXP;
		baseXP < 0.0 ? BaseXP = 3.0f : BaseXP = baseXP;
	}
};
