#include "../include/physicsSystem.h"
#include "../include/particleManager.h"
#include "../include/config.h"
#include <cstdlib>
#include <raylib.h>
#include <raymath.h>
#include "../include/config.h"

PhysicsSystem::PhysicsSystem() {
    this->particlesAreSolid = false;
}


void PhysicsSystem::updatePosition(ParticleManager& particleManager) {
    for (auto e:particleManager.all()) {
        // x pos
        e->pos.x = e->pos.x + e->vel.x * (1.0 / TARGET_FPS);

        // y pos
        e->pos.y = e->pos.y + e->vel.y * (1.0 / TARGET_FPS);
    }
}

void PhysicsSystem::addForces(ParticleManager& particleManager) {
    for (auto e:particleManager.all()) {
        // Gravity
        e->vel = Vector2Add(e->vel, Forces::gravity());

        // Point Force
        // e->vel = Vector2Add(e->vel, Forces::pointForce(e->pos));
    }
}

void PhysicsSystem::addBorderCollisions(ParticleManager& particleManager) {
    for (auto e:particleManager.all()) {
        // Collisions
        if (e->pos.x - PARTICLE_RADIUS < 0) {
            e->pos.x = 0 + PARTICLE_RADIUS;
            e->vel.x = -e->vel.x;
        }

        if (e->pos.x + PARTICLE_RADIUS > WINDOW_WIDTH) {
            e->pos.x = WINDOW_WIDTH - PARTICLE_RADIUS;
            e->vel.x = -e->vel.x;
        }

        if (e->pos.y + PARTICLE_RADIUS > WINDOW_HEIGHT) {
            e->pos.y = WINDOW_HEIGHT - PARTICLE_RADIUS;
            e->vel.y = -e->vel.y;
        }

        if (e->pos.y - PARTICLE_RADIUS < 0) {
            e->pos.y = 0 + PARTICLE_RADIUS;
            e->vel.y = -e->vel.y;
        }
    }
}

void PhysicsSystem::addSolidParticles(ParticleManager& particleManager) {
    this->particlesAreSolid = true;
    for (auto e1:particleManager.all()) {
        for (auto e2: particleManager.all()) {
            if (e1->id == e2->id) {
                continue;
            }

            // Calculate distance
            float dist = Vector2Distance(e1->pos, e2->pos);

            bool colided = dist < 2 * PARTICLE_RADIUS;

            if (colided) {
                float halfOverlap = 0.5f * (2 * PARTICLE_RADIUS - dist);
                
                Vector2 direc1 = Vector2Normalize(Vector2Subtract(e1->pos, e2->pos)) ;
                direc1 = Vector2Scale(direc1, halfOverlap);
                Vector2 direc2 = Vector2Negate(direc1);

                e1->pos = (Vector2) {e1->pos.x + direc1.x, e1->pos.y + direc1.y};
                e2->pos = (Vector2) {e2->pos.x + direc2.x, e2->pos.y + direc2.y};
            }

        }
    }
}

void PhysicsSystem::addConservationOfMomentum(ParticleManager& particleManager) {
    if (!this->particlesAreSolid) {
        return ;
    }
    for (auto e1:particleManager.all()) {
        for (auto e2: particleManager.all()) {
            if (e1->id <= e2->id) {
                continue;
            }
            
            if (CheckCollisionCircles(e1->pos, PARTICLE_RADIUS, e2->pos, PARTICLE_RADIUS)) {
                // Conservation of momentum
                Vector2 c12_diff = Vector2Subtract(e1->pos, e2->pos);
                Vector2 v12_diff = Vector2Subtract(e1->vel, e2->vel);
                float c12_diff_len = Vector2Length(c12_diff);

                float scaleFactor = -1 * Vector2DotProduct(v12_diff, c12_diff) / (c12_diff_len * c12_diff_len);
            
                Vector2 dv_1 = Vector2Scale(c12_diff, scaleFactor);
                Vector2 dv_2 = Vector2Scale(c12_diff, -scaleFactor);

                e1->vel = Vector2Add(e1->vel, dv_1);
                e2->vel = Vector2Add(e2->vel, dv_2);
            }
        }
    }
}

void PhysicsSystem::update(ParticleManager& particleManager) {
    this->addConservationOfMomentum(particleManager);
    this->addSolidParticles(particleManager);
    this->addBorderCollisions(particleManager);
    this->addForces(particleManager);
    this->updatePosition(particleManager);
}