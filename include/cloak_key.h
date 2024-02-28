#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

bool HandleKey_Hook(UINT keyId, BYTE unk);

bool HandleKey_Original(UINT keyId, BYTE unk);
