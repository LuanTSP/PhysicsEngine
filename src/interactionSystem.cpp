#include "../include/interactionSystem.h"
#include <raylib.h>


InteractionSystem::InteractionSystem() {
    this->selected = nullptr;
};

void InteractionSystem::handleMouseLeftClick(ParticleManager& particleManager) {
    if (IsMouseButtonPressed(0)) {
        Vector2 mousePos = GetMousePosition();
        particleManager.createParticle(mousePos, {0, 0});
    }
}

void InteractionSystem::handleMouseMiddleClick(ParticleManager& particleManager) {
    // CLICK AND DRAG FUNCTIONALITY =>
    if (IsMouseButtonDown(2)) {
        if (this->selected != nullptr) {
            Vector2 mousePos = GetMousePosition();
            selected->pos = mousePos;
            selected->vel = {0, 0};
        } else {
            Vector2 mousePos = GetMousePosition();
            for (auto e:particleManager.all()) {
                float distance = Vector2Distance(e->pos, mousePos);
                if (distance < PARTICLE_RADIUS) {
                    this->selected = e;
                    break;
                }
            }
        }
    }

    if (IsMouseButtonReleased(2)) {
        this->selected = nullptr;
    }
}

void InteractionSystem::handleMouseRightClick(ParticleManager& particleManager) {
    if (IsMouseButtonDown(1)) {
        Vector2 mousePos = GetMousePosition();
        DrawCircleLines(mousePos.x, mousePos.y, 20, {255, 0, 0, 255});
        for (auto e:particleManager.all()) {
            if (CheckCollisionCircles(mousePos, 20, e->pos, PARTICLE_RADIUS)) {
                particleManager.deleteParticle(e->id);
            }
        }
    }
}

void InteractionSystem::update(ParticleManager& particleManager) {
    this->handleMouseLeftClick(particleManager);
    this->handleMouseMiddleClick(particleManager);
    this->handleMouseRightClick(particleManager);
}