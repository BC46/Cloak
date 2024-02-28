#include "cloak_key.h"
#include "Freelancer.h"

#define Naked __declspec(naked)

#define HANDLE_KEY_SECOND_INSTR_ADDR HANDLE_KEY_ADDR + 0x6

void DoCloak()
{
    // TODO: Implement
}

bool HandleKey_Hook(UINT keyId, BYTE unk)
{
    // If the cloak key is pressed, we handle it ourselves
    if (keyId == CLOAK_KEY_IDENTIFIER)
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
