#include "../include/particleManager.h"
#include "../include/config.h"
#include <raylib.h>

// ================ ENTITY ================ //
Particle::Particle(int id, Vector2 pos, Vector2 vel, Color color) {
    this->id = id;
    this->pos = pos;
    this->vel = vel;
    this->color = color;
}


void Particle::draw() {
    DrawCircle(this->pos.x, this->pos.y, PARTICLE_RADIUS, this->color);
}


// ================ PERTICLE MANAGER ================ //
ParticleManager::ParticleManager() {
    this->current_id = 0;
    this->count = 0;
}

ParticleManager::~ParticleManager() {
    for (auto e:this->entities) {
        delete e;
    }
}

Particle* ParticleManager::createParticle(Vector2 pos, Vector2 vel) {
    Color defaultColor = (Color) {255,255,255,255};
    Particle* new_particle = new Particle(current_id, pos, vel, defaultColor);
    this->entities.push_back(new_particle);
    this->current_id++;
    this->count++;

    return new_particle;
}

void ParticleManager::update() {
    for (int id:to_delete) {
        for (int j=0; j < count; j++) {
            if (entities[j]->id == id) {
                Particle* e = entities[j];
                entities.erase(entities.begin() + j);
                delete e;
                count--;
                break;
            }
        }
    }
    this->to_delete.clear();
}

void ParticleManager::deleteParticle(int id) {
    this->to_delete.push_back(id);
}

std::vector<Particle*> ParticleManager::all() {
    return this->entities;
}

void ParticleManager::logSummary() {
    std::cout << "Particle Count: " << count << "\nIDs: ";
    for (auto e:entities) {
        std::cout << e->id << " ";
    }
    std::cout << "\n";
}