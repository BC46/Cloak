#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define Import __declspec(dllimport)

#define CLOAKING_DEVICE_TYPE 0x1000

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

    // NOTE: Do NOT call the _vftable functions unless documented;
    // they are there to set the correct offsets in the vftable for the functions we actually want to call
    virtual void x00_vftable();
    virtual void x04_vftable();
    virtual void x08_vftable();
    virtual void x0C_vftable();
    virtual void x10_vftable();
    virtual void x14_vftable();
    virtual void x18_vftable();
    virtual void x1C_vftable();
    virtual void x20_vftable();
    virtual void x24_vftable();
    virtual void x28_vftable();
    virtual void x2C_vftable();
	virtual bool Activate(bool val);
};

struct IObjInspectImpl
{
    BYTE data[16];
    CShip* ship;
};
