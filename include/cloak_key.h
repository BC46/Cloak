#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Common.h"

bool HandleKey_Hook(UINT keyId, BYTE unk);

bool HandleKey_Original(UINT keyId, BYTE unk);

bool __fastcall ActivateCloak_Hook(CECloakingDevice* cd, PVOID _edx, bool activate);

bool PostInitSinglePlayer_Hook();
