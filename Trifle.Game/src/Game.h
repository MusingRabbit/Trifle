#ifndef GAME_H
#define GAME_H

#include <GLGameWindow.h>
#include <Core/EntityService.h>
#include <memory>

using namespace trifle;

class Game
{
  private:
    std::unique_ptr<EntityService> m_enttySvc;
    std::unique_ptr<GLGameWindow> m_gameWindow;

  protected:
  public:
    Game();

    int Run();

    virtual ~Game();
};

#endif // !GAME_H