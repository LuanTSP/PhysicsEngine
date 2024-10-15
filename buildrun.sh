#!/usr/bin/sh

g++ main.cpp src/particleManager.cpp src/physicsSystem.cpp src/renderingSystem.cpp src/interactionSystem.cpp -l raylib -o physics


if [ $? -eq 0 ]; then
    echo "Build complete!"
    ./physics
else
    echo "Error on build!"
fi