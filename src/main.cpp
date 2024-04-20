#include "utils.h"
#include "Freelancer.h"
#include "cloak_key.h"
#include "config.h"

void Init()
{
    // Hook call
    Hook(HANDLE_KEY_ADDR, (DWORD) HandleKey_Hook, 6, true);

    CloakingStrategy strategy = GetCloakingStrategy();

    if (strategy == AutomaticallyUncloakCS)
    {
        static PVOID singlePlayerPtr = PostInitSinglePlayer_Hook;
        SetPointer(POST_INIT_SP_CALL_ADDR, &singlePlayerPtr);
    }
    else if (strategy == InactiveCS)
    {
        DWORD common = (DWORD) GetModuleHandleA("common.dll");
        Hook(common + CLOAKING_DEVICE_ACTIVATE_OFF, (DWORD) ActivateCloak_Hook, 5);
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(hinstDLL);
    UNREFERENCED_PARAMETER(lpReserved);

    if (fdwReason == DLL_PROCESS_ATTACH)
        Init();

    return TRUE;
}
