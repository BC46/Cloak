#include "config.h"
#include "Common.h"

CloakConfig GetConfig()
{
    CloakConfig result{ AutomaticallyUncloakCS, false };
    INI_Reader reader;

    reader.open("cloak.ini");

    while (reader.read_header())
    {
        if (!reader.is_header("Options"))
            continue;

        while (reader.read_value())
        {
            if (reader.is_value("initial_cloak_behavior"))
            {
                int intVal = reader.get_value_int();

                if (intVal >= 0 && intVal <= 2)
                    result.strategy = (CloakingStrategy) intVal;
            }
            else if (reader.is_value("npc_engine_fade"))
            {
                result.useNpcEngineFade = reader.get_value_bool();
            }
        }
    }

    reader.close();

    return result;
}
