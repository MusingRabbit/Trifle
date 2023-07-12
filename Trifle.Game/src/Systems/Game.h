#ifndef GAME_H
#define GAME_H

#include <trifle.h>

using namespace trifle;

class Game : public System
{
  private:
    std::shared_ptr<GLGameWindow> m_gameWindow;
    std::shared_ptr<VoxelGridSystem> m_voxelGrid;
    Camera m_camera;

    void OutputCameraPosition();

  public:
    Game(EntityManager& manager);
    ~Game();

    void Init(std::shared_ptr<GLGameWindow> gameWindow);

    void Init() override;
    void Update(float dt) override;
};

#endif // !GAME_H
