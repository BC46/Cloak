#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Freelancer.h"

void RegisterCloakKeyHandler();

bool __fastcall ActivateCloak_Hook(CECloakingDevice* cd, PVOID _edx, bool activate);

bool PostInitSinglePlayer_Hook();

bool __fastcall HideCockpitModel_Hook(const float& cockpitPerformanceOpt);

class CloakKeyHandler : public KeyHandler
{
    virtual bool HandleKey(DWORD keyId);
};
