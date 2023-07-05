#ifndef GAME_H
#define GAME_H

#include <GLGameWindow.h>
#include <Core/EntityManager.h>
#include <Components/Components.h>
#include <memory>

using namespace trifle;

class Game
{
  private:
    std::shared_ptr<EntityManager> m_entityManager;
    std::unique_ptr<GLGameWindow> m_gameWindow;

    void RegisterComponents();
    void RegisterSystems();
    void InitSystems();
    void GameUpdateSystems(float dt);

  protected:
  public:
    Game();

    void Init();

    int Run();

    virtual ~Game();
};

#endif // !GAME_H