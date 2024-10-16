#pragma once
#include <cstdint>
#include <vector>
#include <raylib.h>
#include <string>
#include <iostream>

class Particle {
    public:
    int id;
    Vector2 pos;
    Vector2 vel;
    Color color;
    
    public:
    Particle(int id, Vector2 pos, Vector2 vel, Color color);
    void draw();
};


class ParticleManager {
    public:
    int current_id;
    int count;
    std::vector<Particle*> entities;
    std::vector<int> to_delete;

    
    public:
    ParticleManager();
    ~ParticleManager();
    Particle* createParticle(Vector2 pos, Vector2 vel);
    void update();
    void deleteParticle(int id);
    void logSummary();
    std::vector<Particle*> all();
};