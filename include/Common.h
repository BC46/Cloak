#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define Import __declspec(dllimport)

class CEquip{};

class Import CEquipManager
{
private:
	BYTE data[0x4];
public:
    CEquip* FindFirst(UINT type);
};

struct CShip
{
private:
    BYTE data[0xE4];
public:
    CEquipManager equipManager;
};

class Import CECloakingDevice;

// Activate Cloaking Device function definition
typedef bool __fastcall ActivateCD(CECloakingDevice* cd, PVOID _edx, bool val);

class Import CECloakingDevice
{
public:
	static CECloakingDevice* cast(CEquip*);
	float cloak_percent() const;

	inline bool Activate(bool val)
	{
		// Get function pointer from the vftable
        ActivateCD* originalFunction = (ActivateCD*) vftable->activate;

        // Call the original ActivateCD function
        return (originalFunction)(this, NULL, val);
	}
private:
    struct CECloakingDevice_vftable
    {
        BYTE funcs[0x30];
        PVOID activate;
    };

    CECloakingDevice_vftable* vftable;
};

struct IObjInspectImpl
{
    BYTE data[16];
    CShip* ship;
};
