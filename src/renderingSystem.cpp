#include "../include/renderingSystem.h"


RenderingSystem::RenderingSystem() {}

void RenderingSystem::update(ParticleManager& particleManager) {
    // Render
    for (auto e:particleManager.all()) {
        e->draw();
    }
}