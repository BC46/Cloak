#pragma once

#include "Common.h"

#define HANDLE_KEY_ADDR 0x576410
#define GET_PLAYERIOBJINSPECTIMPL_ADDR 0x54BAF0
#define POST_INIT_SP_CALL_ADDR 0x54AE3C

#define CLOAK_KEY_IDENTIFIER 0x8E

#define PLAYER_SIMPLE_ID (*(PUINT) 0x673378)

typedef IObjInspectImpl* GetPlayerIObjInspectImpl();
