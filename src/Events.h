#pragma once
#include "Settings.h"

namespace Events
{
	class OnHitEventHandler : public RE::BSTEventSink<RE::TESHitEvent>
	{
	public:

		static OnHitEventHandler* GetSingleton()
		{
			static OnHitEventHandler singleton;
			return std::addressof(singleton);
		}

		RE::BSEventNotifyControl ProcessEvent(const RE::TESHitEvent* a_event, RE::BSTEventSource<RE::TESHitEvent>* a_eventSource) override
		{
			using HitFlag = RE::TESHitEvent::Flag;
			if (!a_event || !a_eventSource) {
				logger::error("Event Source Not Found!");
				return RE::BSEventNotifyControl::kContinue;
			}

			if (!a_event->flags.any(HitFlag::kBashAttack) && a_event->target)
			{
				if (!a_event || !a_event->cause || !a_event->cause->IsPlayerRef() || a_event->target->IsNot(RE::FormType::ActorCharacter) || !a_event->source)
					return RE::BSEventNotifyControl::kContinue;		

				auto defender = a_event->target->As<RE::Actor>();
				auto attackingWeapon = RE::TESForm::LookupByID<RE::TESObjectWEAP>(a_event->source);

				if (!defender || !attackingWeapon || !defender->currentProcess || !defender->currentProcess->high || !attackingWeapon->IsMelee() || !defender->Get3D())
					return RE::BSEventNotifyControl::kContinue;

				auto player = a_event->cause->As<RE::Actor>();
				auto playerAttkData = player->currentProcess->high->attackData;

				if (!playerAttkData)
					return RE::BSEventNotifyControl::kContinue;

				if ((defender->ActorState::GetLifeState() != RE::ACTOR_LIFE_STATE::kDead) && !IsBeastRace() && attackingWeapon->IsHandToHandMelee())
				{
					ApplyHandToHandXP();
				}
			}

			return RE::BSEventNotifyControl::kContinue;					
		}

		static void Register()
		{
			RE::ScriptEventSourceHolder* eventHolder = RE::ScriptEventSourceHolder::GetSingleton();
			eventHolder->AddEventSink(OnHitEventHandler::GetSingleton());
		}

	private:
		inline static void ApplyHandToHandXP()
		{
			auto player = RE::PlayerCharacter::GetSingleton();
			float HandToHandLevel = player->GetActorValue(RE::ActorValue::kLockpicking);

			float baseXP = (Settings::BonusXPPerLevel * HandToHandLevel)+Settings::BaseXP;

			player->AddSkillExperience(RE::ActorValue::kLockpicking, baseXP);	
		}
		OnHitEventHandler() = default;

		static bool IsBeastRace()
		{
			RE::MenuControls* MenuControls = RE::MenuControls::GetSingleton();
			return MenuControls->InBeastForm();
		}
	};

	inline static void Register()
	{
		OnHitEventHandler::Register();
	}

}
