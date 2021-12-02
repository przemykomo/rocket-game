#pragma once

class Scene;

struct GameProperties {
    bool pop = false;
    Scene *toPush = nullptr;
    bool shouldClose = false;
};
