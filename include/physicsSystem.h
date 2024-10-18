#pragma once
#include "config.h"
#include "particleManager.h"
#include <cstddef>
#include <raylib.h>
#include <raymath.h>
#include <vector>

class Forces {
    public:
    static Vector2 gravityDown(float acc);
    static Vector2 gravityUp(float acc);
    static Vector2 gravityRight(float acc);
    static Vector2 gravityLeft(float acc);
    static Vector2 pointForce(Vector2 pos, float acc);
};

class PhysicsSystem {
    bool particlesAreSolid;

    void updatePosition(ParticleManager& particleManager);
    void addForces(ParticleManager& particleManager);
    void addBorderCollisions(ParticleManager& particleManager);
    void addSolidParticles(ParticleManager& particleManager);
    void addConservationOfMomentum(ParticleManager& particleManager);

    public:
    PhysicsSystem();
    void update(ParticleManager& particleManager);
};