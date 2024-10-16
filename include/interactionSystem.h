#pragma once
#include <raylib.h>
#include "../include/particleManager.h"
#include "../include/config.h"
#include <raymath.h>

class InteractionSystem {
    Particle* selected;
        
    private:
    void handleMouseLeftClick(ParticleManager& particleManager);
    void handleMouseMiddleClick(ParticleManager& particleManager);
    void handleMouseRightClick(ParticleManager& particleManager);
    
    public:
    InteractionSystem();
    void update(ParticleManager& particleManager);

};