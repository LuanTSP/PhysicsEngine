#pragma once
#include "particleManager.h"
#include <cstddef>
#include <raylib.h>

class PhysicsSystem {
    void updatePosition(ParticleManager& particleManager);
    void addGravity(ParticleManager& particleManager);
    void addBorderCollisions(ParticleManager& particleManager);
    void addSolidParticles(ParticleManager& particleManager);
    void addConservationOfMomentum(ParticleManager& particleManager);

    public:
    PhysicsSystem();
    void update(ParticleManager& particleManager);
};