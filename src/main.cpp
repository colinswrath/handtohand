#include "Settings.h"
#include "Events.h"
#include "PickpocketReplace.h"
#include "MiscPatches.h"

#include <stddef.h>

void InitListener(SKSE::MessagingInterface::Message* a_msg) noexcept
{
    switch (a_msg->type)
    {
    case SKSE::MessagingInterface::kDataLoaded:
        Events::Register();
        break;
    case SKSE::MessagingInterface::kPostLoadGame:
        break;
    }
}


SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
    Init(skse);

    const auto plugin{ SKSE::PluginDeclaration::GetSingleton() };
    const auto name{ plugin->GetName() };
    const auto version{ plugin->GetVersion() };

    logger::init();
    logger::info("{} {} is loading...", name, version);

    auto messaging = SKSE::GetMessagingInterface();
    if (!messaging->RegisterListener(InitListener)) {
        return false;
    }

    Settings::LoadSettings();
    PickpocketReplace::Install();
    if (!MiscPatches::InstallUnarmedDamagePatch())
    {
        logger::info("Failed to install unarmed damage patch");
        return false;
    }
    else {
        logger::info("Unarmed damage patch installed");
    }

    logger::info("{} has finished loading.", name);

    return true;
}
