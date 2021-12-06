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

		auto bonusXP = (float)ini.GetDoubleValue("HandToHand", "fBonusXPPerLevel", 0.12);
		auto baseXP = (float)ini.GetDoubleValue("HandToHand", "fBaseXPHerHit", 4.0);

		(bonusXP < 0.0 || bonusXP > 100.0) ? BonusXPPerLevel = 0.12f : BonusXPPerLevel = bonusXP;
		baseXP < 0.0 ? BaseXP = 4.0f : BaseXP = baseXP;
	}
};
