#pragma once

namespace PickpocketReplace
{
	inline static std::array<std::uint8_t, 1> SkillIndexReplace{ 0x0D };

	void static Install()
	{
		static REL::Relocation<std::uintptr_t> hook_LockPick{REL::RelocationID(51088,51968), 0x4E};
		static REL::Relocation<std::uintptr_t> hook_LockPickBreak{ REL::RelocationID(51093,51975), 0x234 };

		static REL::Relocation<std::uintptr_t> hook_LockpickMenuSkillLevel{ REL::RelocationID(51084,51963), 0x73 };
		static REL::Relocation<std::uintptr_t> hook_LockpickMenuXPProgress{ REL::RelocationID(51084,51963), 0xCA };

		REL::safe_write<std::uint8_t>(hook_LockPick.address(), SkillIndexReplace);
		REL::safe_write<std::uint8_t>(hook_LockPickBreak.address(), SkillIndexReplace);
		REL::safe_write<std::uint8_t>(hook_LockpickMenuSkillLevel.address(), SkillIndexReplace);
		REL::safe_write<std::uint8_t>(hook_LockpickMenuXPProgress.address(), SkillIndexReplace);
	}
}

