#pragma once
#include "Settings.h"

namespace MiscPatches
{
    inline static REL::Relocation<std::uintptr_t> GetUnarmedDamageHook(REL::RelocationID(25851, 26420)); //Incorrect 1.5 address

    void GetUnarmedDamage(RE::ActorValueOwner* avOwner, float* result)
    {
        float damage = 0;
        if (avOwner) {
            damage = avOwner->GetActorValue(RE::ActorValue::kUnarmedDamage);
            damage += avOwner->GetActorValue(RE::ActorValue::kLockpicking) * Settings::h2hUnarmedScalingFactor; // Lockpicking = h2h
        }
        *result = damage;
    }

    bool InstallUnarmedDamagePatch()
    {

        struct unarmedDmg : Xbyak::CodeGenerator
        {
            unarmedDmg()
            {
                mov(rax, reinterpret_cast<std::uintptr_t>(GetUnarmedDamage));
                jmp(rax);
            }
        };

        auto patch = new unarmedDmg();
        patch->ready();

        REL::safe_write(GetUnarmedDamageHook.address(), patch->getCode(), patch->getSize());
        return true;
    }
}
