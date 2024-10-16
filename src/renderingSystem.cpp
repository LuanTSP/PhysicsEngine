#include "../include/renderingSystem.h"

RenderingSystem::RenderingSystem() {}

void RenderingSystem::renderParticles(ParticleManager& particleManager) {
    for (auto e:particleManager.all()) {
        e->draw();
    }
}


void RenderingSystem::renderSystemInfo(ParticleManager& particleManager) {
    // Calculate Total Energy
    float totalEnergy = 0;

    for (auto e:particleManager.all()) {
        Vector2 v = e->vel;
        totalEnergy += 0.5 * (v.x * v.x + v.y * v.y);
        totalEnergy += GRAVITY * 100 * (WINDOW_HEIGHT - e->pos.y);
    }
    
    std::string text = "System Info\nTotal Energy: ";
    text += std::to_string((int)totalEnergy);

    // Number of Particles
    text += "\nParticles: ";
    text += std::to_string(particleManager.count);

    // Draw Text
    DrawText(text.c_str(), 0, 0, 16, {255, 255, 255, 255});
}

void RenderingSystem::update(ParticleManager& particleManager) {
    this->renderParticles(particleManager);
    this->renderSystemInfo(particleManager);
}