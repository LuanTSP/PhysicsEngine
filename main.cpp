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

    // Game Loop
    float max = 0;
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

        if (max < 200) {
            particleManager.createParticle({400, 200}, {-100 , -100});
            particleManager.createParticle({401, 200}, {-100 , 100});
            particleManager.createParticle({402, 200}, {100 , -100});
            particleManager.createParticle({403, 200}, {100 , 100});
            max++;
        }

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}