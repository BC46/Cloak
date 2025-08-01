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

bool (*HandleKey_Original)(UINT keyId, BYTE unk);

void SetOriginalHandleKeyFunc(bool (*func)(UINT keyId, BYTE unk))
{
    HandleKey_Original = func;
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

bool __fastcall ActivateCloak_Hook(CECloakingDevice* cd, PVOID _edx, bool activate)
{
    CShip* playerShip = GetPlayerShip();

    // playerShip is null when the cloak is initially activated by the player
    if (!playerShip || cd->parent == playerShip)
    {
        // The initial cloaking state should only be false for the player in SP
        return cd->Activate( SinglePlayer() ? false : activate );
    }

    // If the cloaking device is not activated by the player, just use the given value
    // Otherwise if a storyline NPC with a cloaking device is spawned, then it may not get in the desired state
    return cd->Activate(activate);
}

// Hook for SP function that gets called right after initializing the player's ship (undock or load game in space)
// This is where we want to deactivate the cloak
bool PostInitSinglePlayer_Hook()
{
    DoCloak();

    // Call original function
    return SinglePlayer();
}
