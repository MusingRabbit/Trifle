#ifndef PROGRAM_H
#define PROGRAM_H

#include <GameWindow.h>
#include <Graphics/Renderer.h>

class Program
{
private : 
    GameWindow* m_gameWindow;
    Renderer* m_renderer;

protected:
public : 
    Program();

    int Run();

    virtual ~Program();
};

#endif // !PROGRAM_H