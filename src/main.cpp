#include "utils.h"
#include "Freelancer.h"
#include "cloak_key.h"
#include "config.h"

void Init()
{
    // Hook call
    bool (*handleKeyOriginal)(UINT keyId, BYTE unk) = AbsTrampoline(HANDLE_KEY_ADDR, HandleKey_Hook, 7);
    SetOriginalHandleKeyFunc(handleKeyOriginal);

    CloakConfig cloakConfig = GetConfig();

    if (cloakConfig.strategy == AutomaticallyUncloakCS)
    {
        static PVOID singlePlayerPtr = PostInitSinglePlayer_Hook;
        SetPointer(POST_INIT_SP_CALL_ADDR, &singlePlayerPtr);
    }
    else if (cloakConfig.strategy == InactiveCS)
    {
        DWORD common = (DWORD) GetModuleHandleA("common.dll");

        // Check if Common.dll is 1.1 or 1.0 and apply the hook at the right location
        PBYTE commonVerCheckByte = (PBYTE) common + CLOAKING_DEVICE_ACTIVATE_OFF_V1_0;
        ReadWriteProtect((DWORD) commonVerCheckByte, sizeof(commonVerCheckByte));
        DWORD patchOffset = *commonVerCheckByte == 0x3A
            ? CLOAKING_DEVICE_ACTIVATE_OFF_V1_1 : CLOAKING_DEVICE_ACTIVATE_OFF_V1_0;

        Hook(common + patchOffset, (DWORD) ActivateCloak_Hook, 5);
    }

    #define USE_NPC_ENGINE_FADE_ADDR (0x528A8D)
    ReadWriteProtect(USE_NPC_ENGINE_FADE_ADDR, sizeof(BYTE));
    *((PBYTE) USE_NPC_ENGINE_FADE_ADDR)
        = cloakConfig.useNpcEngineFade ? 0x18 : 0x1C;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);

    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinstDLL);
        Init();
    }

    return TRUE;
}
