#pragma once

#include "Common.h"

#define GET_PLAYERIOBJINSPECTIMPL_ADDR 0x54BAF0
#define POST_INIT_SP_CALL_ADDR 0x54AE3C
#define REGISTER_KEY_HANDLER_ADDR 0x575E00

#define CLOAK_KEY_IDENTIFIER 0x8E

#define PLAYER_SIMPLE_ID (*(PUINT) 0x673378)

typedef IObjInspectImpl* GetPlayerIObjInspectImpl();

class KeyHandler
{
public:
    virtual bool HandleKey(DWORD keyId) = 0;
};
