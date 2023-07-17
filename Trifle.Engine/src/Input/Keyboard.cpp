#include "Keyboard.h"

namespace tfl
{
KeyboardState Keyboard::KbState = KeyboardState();

KeyboardState Keyboard::GetState()
{
    return KbState;
}

void Keyboard::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    switch (action)
    {
    case GLFW_PRESS:
        KbState.SetKey((Keys)key);
        break;
    case GLFW_RELEASE:
        KbState.ClearKey((Keys)key);
        break;
    case GLFW_REPEAT:
        /* code */
        break;
    default:
        break;
    }
    }
}