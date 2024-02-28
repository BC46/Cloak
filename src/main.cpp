#include "utils.h"
#include "Freelancer.h"
#include "cloak_key.h"

void Init()
{
    // Hook call
    Hook(HANDLE_KEY_ADDR, (DWORD) HandleKey_Hook, 6, true);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(hinstDLL);
    UNREFERENCED_PARAMETER(lpReserved);

    if (fdwReason == DLL_PROCESS_ATTACH)
        Init();

    return TRUE;
}
