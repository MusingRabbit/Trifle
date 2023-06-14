#ifndef GAME_H
#define GAME_H

#include <GameWindow.h>
#include <Graphics/Renderer.h>
#include <Core/GameObject.h>

class Game
{
private : 
    trifle::GameWindow* m_gameWindow;
    trifle::Renderer* m_renderer;

protected:
public : 
    Game();

    int Run();

    virtual ~Game();
};

#endif // !GAME_H