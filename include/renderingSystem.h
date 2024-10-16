#pragma once
#include "particleManager.h"
#include "config.h"

class RenderingSystem {
    void renderParticles(ParticleManager& particleManager);
    void renderSystemInfo(ParticleManager& particleManager);
    
    public:
    RenderingSystem();
    void update(ParticleManager& particleManager);
};