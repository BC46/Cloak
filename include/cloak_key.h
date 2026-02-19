#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Common.h"

void SetOriginalHandleKeyOriginalFunc(bool (*func)(UINT keyId, BYTE unk));

void SetOriginalHandleKeyFunc(bool (*func)(UINT keyId, BYTE unk));

bool HandleKey_Hook(UINT keyId, BYTE unk);

bool __fastcall ActivateCloak_Hook(CECloakingDevice* cd, PVOID _edx, bool activate);

bool PostInitSinglePlayer_Hook();

bool __fastcall HideCockpitModel_Hook(const float& cockpitPerformanceOpt);
