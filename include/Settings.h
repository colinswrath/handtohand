#pragma once
#include <SimpleIni.h>

class Settings
{
public:
	inline static float BonusXPPerLevel;
	inline static float BaseXP;
    inline static float h2hUnarmedScalingFactor;

	static void LoadSettings();
};
