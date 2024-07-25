#ifndef GAME_H
#define GAME_H

#include <trifle.h>

using namespace tfl;

class Game : public System
{
  private:
    std::shared_ptr<VoxelGridSystem> m_gridSys;

    Camera m_camera;
    GameTimer m_gameTimer;

    void OutputCameraPosition();
    void OutputCameraTarget();
    void OutputFrameTime();
  public:
    Game(unsigned int id, const SystemContext& context);
    ~Game();

    void Init(std::shared_ptr<GameWindow> gameWindow);

    void Init() override;
    
    void Update() override;

    void OnEntityAdded(unsigned int entityId) override;
    void OnEntityRemoved(unsigned int entityId) override;
    
};

#endif // !GAME_H
