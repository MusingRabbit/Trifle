#ifndef GAME_H
#define GAME_H

#include <trifle.h>

using namespace tfl;

class Game : public System
{
  private:
    std::shared_ptr<VoxelGridSystem> m_voxelGrid;
    Camera m_camera;

    void OutputCameraPosition();

  public:
    Game(unsigned int id, const SystemContext& context);
    ~Game();

    void Init(std::shared_ptr<GameWindow> gameWindow);

    void Init() override;
    void Update(float dt) override;
};

#endif // !GAME_H
