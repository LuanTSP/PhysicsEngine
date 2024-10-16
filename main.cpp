#include <raylib.h>
#include "include/interactionSystem.h"
#include "include/particleManager.h"
#include "include/physicsSystem.h"
#include "include/renderingSystem.h"
#include "include/config.h"

int main() {
    // Parameters
    SetTraceLogLevel(LOG_ERROR);
    
    SetTargetFPS(TARGET_FPS);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    ParticleManager particleManager = ParticleManager();
    PhysicsSystem physicsSystem = PhysicsSystem();
    RenderingSystem renderingSystem = RenderingSystem();
    InteractionSystem interactionSystem = InteractionSystem();

    particleManager.createParticle({100, 200}, {0, 0});
    particleManager.createParticle({300, 200}, {0, 0});
    particleManager.createParticle({400, 300}, {0, 0});
    particleManager.createParticle({100, 300}, {0, 0});
    particleManager.createParticle({100, 400}, {0, 0});
    particleManager.createParticle({300, 100}, {0, 0});


    // Game Loop
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground((Color){0,0,0,255});
        
        // Pause Function
        if (!IsKeyDown(KEY_SPACE)) {
            particleManager.update();
            physicsSystem.update(particleManager);
        }
        renderingSystem.update(particleManager);
        interactionSystem.update(particleManager);

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}