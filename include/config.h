enum CloakingStrategy
{
    VanillaCS,
    AutomaticallyUncloakCS,
    InactiveCS
};

struct CloakConfig
{
    CloakConfig()
        : strategy(AutomaticallyUncloakCS),
        useNpcEngineFade(false),
        hideCockpitWhileCloaked(false)
    {};

    CloakingStrategy strategy;
    bool useNpcEngineFade;
    bool hideCockpitWhileCloaked;
};

CloakConfig GetConfig();
