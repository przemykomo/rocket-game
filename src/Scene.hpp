#pragma once
#include <functional>

class Scene {
  private:
    bool &pop;
    Scene *&toPush;

  protected:
    Scene(bool &pop, Scene *&toPush);

  public:
    virtual void frame() = 0;
    virtual ~Scene() = default;
    void exitScene();
    void openScene(std::function<Scene *(bool &, Scene *&)> constructor);
};
