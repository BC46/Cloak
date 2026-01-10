enum CloakingStrategy
{
    VanillaCS,
    AutomaticallyUncloakCS,
    InactiveCS
};

struct CloakConfig
{
    CloakingStrategy strategy;
    bool useNpcEngineFade;
};

CloakConfig GetConfig();
