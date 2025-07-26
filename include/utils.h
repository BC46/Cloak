#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void Patch(LPVOID vOffset, LPVOID mem, UINT len);

void Nop(LPVOID vOffset, UINT len);

void Hook(DWORD location, DWORD hookFunc, UINT instrLen, bool jmp = false);

void SetPointer(DWORD location, PVOID p);

inline void ReadWriteProtect(DWORD location, DWORD size)
{
    DWORD _;
    VirtualProtect((PVOID) location, size, PAGE_EXECUTE_READWRITE, &_);
}

template <class Func>
inline Func GetFuncDef(DWORD funcAddr)
{
    return *(Func*) &funcAddr;
}

void AbsHook(DWORD location, DWORD hookFunc, UINT instrLen, bool jmp);

template <typename Func>
Func AbsTrampoline(DWORD location, Func hookFunc, UINT instrLen)
{
    // Allocate memory for gateway function.
    PBYTE gatewayFunc = (PBYTE) VirtualAlloc(NULL, instrLen + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    // Copy the instruction(s) that will be overwritten by setting the hooks to the gateway code.
    ReadWriteProtect(location, instrLen);
    memcpy(gatewayFunc, (PVOID) location, instrLen);

    // Jmp from location to hook function.
    AbsHook(location, (DWORD) hookFunc, instrLen, true);
    // Jmp from gateway to original function.
    Hook((DWORD) (gatewayFunc + instrLen), location + instrLen, 5, true);

    // Return handle for calling the gateway function which in turn calls the original function.
    return GetFuncDef<Func>((DWORD) gatewayFunc);
}
