#include "utils.h"

void Patch(DWORD vOffset, LPVOID mem, UINT len)
{
    ReadWriteProtect(vOffset, len);
    memcpy((PVOID) vOffset, mem, len);
}

void Nop(LPVOID vOffset, UINT len)
{
    static DWORD _;

    VirtualProtect(vOffset, len, PAGE_EXECUTE_READWRITE, &_);
    memset(vOffset, 0x90, len);
}

void Hook(DWORD location, DWORD hookFunc, UINT instrLen, bool jmp)
{
    // Set the opcode for the call or jmp instruction
    static BYTE callOpcode = 0xE8, jmpOpcode = 0xE9;
    Patch(location, &(jmp ? jmpOpcode : callOpcode), sizeof(BYTE));

    // Set and calculate the relative offset for the hook function
    DWORD relOffset = hookFunc - location - 5;
    Patch(location + 1, &relOffset, sizeof(DWORD));

    // Nop out excess bytes
    if (instrLen > 5)
        Nop((PVOID) (location + 5), instrLen - 5);
}

void AbsHook(DWORD location, DWORD hookFunc, UINT instrLen, bool jmp)
{
    // Set the mov opcode
    BYTE movOpcode = 0xB8;
    Patch(location, &movOpcode, sizeof(BYTE));

    // Set the absolute address of the hook function
    Patch(location + 1, &hookFunc, sizeof(DWORD));

    // Set the opcode for the call or jmp instruction
    static WORD callOpcode = 0xD0FF, jmpOpcode = 0xE0FF;
    Patch(location + 5, &(jmp ? jmpOpcode : callOpcode), sizeof(callOpcode));

    // Nop out excess bytes
    if (instrLen > 7)
        Nop((PVOID) (location + 7), instrLen - 7);
}

void SetPointer(DWORD location, PVOID p)
{
    DWORD pRef = (DWORD) &p;
    Patch(location, (PVOID) pRef, sizeof(DWORD));
}
