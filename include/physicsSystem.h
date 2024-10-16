#pragma once
#include "config.h"
#include "particleManager.h"
#include <cstddef>
#include <raylib.h>
#include <raymath.h>
#include <vector>

class Forces {
    public:
    static Vector2 gravity() {
        return (Vector2) {0, GRAVITY * 100 * (1.0 / TARGET_FPS)};
    }

    static Vector2 pointForce(Vector2 pos) {
        Vector2 centerPos = GetMousePosition();
        float distance = Vector2Distance(pos, centerPos);
        Vector2 direction = Vector2Normalize(Vector2Subtract(centerPos, pos));
        return Vector2Scale(direction, 2 * GRAVITY * 100 * (1.0 / TARGET_FPS));
    }
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