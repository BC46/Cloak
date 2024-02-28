#include "cloak_key.h"
#include "Freelancer.h"

#define Naked __declspec(naked)

#define HANDLE_KEY_SECOND_INSTR_ADDR HANDLE_KEY_ADDR + 0x6

CShip* GetPlayerShip()
{
    IObjInspectImpl* playerIObjInspect = ((GetPlayerIObjInspectImpl*) GET_PLAYERIOBJINSPECTIMPL_ADDR)();
    return !playerIObjInspect ? NULL : playerIObjInspect->ship;
}

void DoCloak()
{
    CShip* playerShip = GetPlayerShip();

    if (!playerShip)
        return;

    CECloakingDevice* cd = CECloakingDevice::cast(playerShip->equipManager.FindFirst(CLOAKING_DEVICE_TYPE));

    if (!cd)
        return;

    float cloakPercent = cd->cloak_percent();

    if (cloakPercent == 0.0f)
        cd->Activate(true);
    else if (cloakPercent == 1.0f)
        cd->Activate(false);
}

bool HandleKey_Hook(UINT keyId, BYTE unk)
{
    // If the cloak key is pressed and we are in SP, we handle it ourselves
    if (keyId == CLOAK_KEY_IDENTIFIER && SinglePlayer())
    {
        DoCloak();
        return true;
    }

    // If any other key is pressed, we let the game handle it
    return HandleKey_Original(keyId, unk);
}

bool Naked HandleKey_Original(UINT keyId, BYTE unk)
{
    __asm {
        sub     esp, 0x80                       // Overwritten instruction
        push    HANDLE_KEY_SECOND_INSTR_ADDR
        ret                                     // Call the rest of the original function
    }
}
