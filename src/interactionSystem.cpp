#include "../include/interactionSystem.h"


InteractionSystem::InteractionSystem() {
    this->selected = nullptr;
};

void InteractionSystem::handleMouseLeftClick(ParticleManager& particleManager) {
    // CLICK AND DRAG FUNCTIONALITY =>
    if (IsMouseButtonDown(0)) {
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

    if (IsMouseButtonReleased(0)) {
        this->selected = nullptr;
    }
}

void InteractionSystem::update(ParticleManager& particleManager) {
    this->handleMouseLeftClick(particleManager);
}