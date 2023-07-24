#pragma once

#include <array>
#include <GLFW/glfw3.h>

namespace tfl
{
enum Keys
{
    Unknown     = -1,           //!< Unhandled key
    Space       = 32,           //!< The Space key
    Apostrophe  = 39,           //!< The ' key
    Comma       = 44,           //!< The , key
    Hyphen      = 45,           //!< The - key (hyphen)
    Period      = 46,           //!< The . key
    Slash       = 47,           //!< The / key
    Num0        = 48,           //!< The 0 key
    Num1        = 49,           //!< The 1 key
    Num2        = 50,           //!< The 2 key
    Num3        = 51,           //!< The 3 key
    Num4        = 52,           //!< The 4 key
    Num5        = 53,           //!< The 5 key
    Num6        = 54,           //!< The 6 key
    Num7        = 55,           //!< The 7 key
    Num8        = 56,           //!< The 8 key
    Num9        = 57,           //!< The 9 key
    Semicolon   = 59,           //!< The ; key
    Equal       = 61,           //!< The = key
    A           = 65,           //!< The A key
    B           = 66,           //!< The B key
    C           = 67,           //!< The C key
    D           = 68,           //!< The D key
    E           = 69,           //!< The E key
    F           = 70,           //!< The F key
    G           = 71,           //!< The G key
    H           = 72,           //!< The H key
    I           = 73,           //!< The I key
    J           = 74,           //!< The J key
    K           = 75,           //!< The K key
    L           = 76,           //!< The L key
    M           = 77,           //!< The M key
    N           = 78,           //!< The N key
    O           = 79,           //!< The O key
    P           = 80,           //!< The P key
    Q           = 81,           //!< The Q key
    R           = 82,           //!< The R key
    S           = 83,           //!< The S key
    T           = 84,           //!< The T key
    U           = 85,           //!< The U key
    V           = 86,           //!< The V key
    W           = 87,           //!< The W key
    X           = 88,           //!< The X key
    Y           = 89,           //!< The Y key
    Z           = 90,           //!< The Z key
    LBracket    = 91,           //!< The [ key
    Backslash   = 92,           //!< The \ key
    RBracket    = 93,           //!< The ] key
    Grave       = 96,           //!< The ` key
    World1      = 161,          //non-US #1
    World2      = 162,          //non-US #2
    Escape      = 256,          //!< The Escape key
    Return      = 257,          //!< The Enter/Return keys
    Tab         = 258,          //!< The Tabulation key
    Backspace   = 259,          //!< The Backspace key
    Insert      = 260,          //!< The Insert key
    Delete      = 261,          //!< The Delete key
    Right       = 262,          //!< Right arrow
    Left        = 263,          //!< Left arrow
    Down        = 264,          //!< Down arrow
    Up          = 265,          //!< Up arrow
    PageUp      = 266,          //!< The Page up key
    PageDown    = 267,          //!< The Page down key
    Home        = 268,          //!< The Home key
    End         = 269,          //!< The End key
    CapsLock    = 280,          //!< The CAPS LOCK key
    ScrollLock  = 281,          //!< The SCROLL LOCK key
    NumLock     = 282,          //!< The NUM LOCK key
    PrintScn    = 283,          //!< The Print Screen key
    Pause       = 284,          //!< The Pause key
    F1          = 290,          //!< The F1 key
    F2          = 291,          //!< The F2 key
    F3          = 292,          //!< The F3 key
    F4          = 293,          //!< The F4 key
    F5          = 294,          //!< The F5 key
    F6          = 295,          //!< The F6 key
    F7          = 296,          //!< The F7 key
    F8          = 297,          //!< The F8 key
    F9          = 298,          //!< The F9 key
    F10         = 299,          //!< The F10 key
    F11         = 300,          //!< The F11 key
    F12         = 301,          //!< The F12 key
    F13         = 302,          //!< The F13 key
    F14         = 303,          //!< The F14 key
    F15         = 304,          //!< The F15 key
    F16         = 305,          //!< The F16 key
    F17         = 306,          //!< The F17 key
    F18         = 307,          //!< The F18 key
    F19         = 308,          //!< The F19 key
    F20         = 309,          //!< The F20 key
    F21         = 310,          //!< The F20 key
    F22         = 311,          //!< The F22 key
    F23         = 312,          //!< The F23 key
    F24         = 313,          //!< The F24 key
    F25         = 314,          //!< The F25 key
    Numpad0     = 320,          //!< The numpad 0 key
    Numpad1     = 321,          //!< The numpad 1 key
    Numpad2     = 322,          //!< The numpad 2 key
    Numpad3     = 323,          //!< The numpad 3 key
    Numpad4     = 324,          //!< The numpad 4 key
    Numpad5     = 325,          //!< The numpad 5 key
    Numpad6     = 326,          //!< The numpad 6 key
    Numpad7     = 327,          //!< The numpad 7 key
    Numpad8     = 328,          //!< The numpad 8 key
    Numpad9     = 329,          //!< The numpad 9 key
    NpDecimal   = 330,           //!< The numpad . key
    NpDivide    = 331,          //!< The numpad / key
    NpMultiply  = 332,          //!< The numpad * key
    NpSubtract  = 333,          //!< The numpad - key
    NpAdd       = 334,          //!< The numpad + key
    NpEnter     = 335,          //!< The numpad enter key
    NpEqual     = 336,          //!< The numpad = key
    LShift      = 340,          //!< The left Shift key
    LControl    = 341,          //!< The left Control key
    LAlt        = 342,          //!< The left Alt key
    LSystem     = 343,          //!< The left OS specific key: window (Windows and Linux), apple (macOS), ...
    RShift      = 344,          //!< The right Shift key
    RControl    = 345,          //!< The right Control key
    RAlt        = 346,          //!< The right Alt key
    RSystem     = 347,          //!< The right OS specific key: window (Windows and Linux), apple (macOS), ...
    Menu        = 348,          //!< The Menu key
};

struct KeyboardState
{
    private :
    const char m_capsLockModifier = 1;
    const char m_numLockModifier = 2;
    
    std::array<unsigned int, 10> m_keys;
    
    char m_modifiers;

    public : 
    KeyboardState()
    {
       ClearAllKeys();
    }

    KeyboardState(const KeyboardState& rhs)
    {
        for (unsigned int i = 0; i < m_keys.size(); i++)
        {
            m_keys[i] = rhs.m_keys[i];
        }

        m_modifiers = rhs.m_modifiers;
    }

    /// @brief Gets the current state of the caps lock key.
    /// @return Is active? (true / false)
    bool CapsLock() 
    {
        return (m_modifiers & 1) > 0;
    }

    /// @brief Gets the current state of the numlock key
    /// @return Is active? (true / false)
    bool NumLock()
    {
        return (m_modifiers & 2) > 0;
    }

    void SetModifiers(bool capsLock, bool numLock)
    {
        m_modifiers = (char)(0u | (capsLock ? 1u : 0u) | (numLock ? 2u : 0u));
    }

    /// @brief Sets the state of the specified key to active
    /// @param key Key to be set
    void SetKey(Keys key, bool isActive = true)
    {
        unsigned int keyIdx = 1;//(unsigned int)(int)key >> 5;
        unsigned int num = ((unsigned int)1 << ((int)key & 31));
        unsigned int currKey = m_keys[keyIdx];

        unsigned int value = 0;

        if (isActive)
        {
            value = currKey |= num;
        }
        else 
        {
            value = currKey &= ~num;
        }

        m_keys[keyIdx] = value;
    }

    void ClearKey(Keys key)
    {
        SetKey(key, false);
    }

    /// @brief Check whether the specified key has been pressed.
    /// @param key Key to be checked.
    /// @return Is down? (true / false)
    bool IsKeyDown(Keys key)
    {
        unsigned int idx =  (unsigned int)(int)key >> 5;
        unsigned int num = (unsigned int)(1 << ((int)key & 31));
        return (m_keys[idx] & num) != 0;
    }

    /// @brief Check whether the specified key has been pressed.
    /// @param key Key to be checked.
    /// @return Is up? (true / false)
    bool IsKeyUp(Keys key)
    {
        return !IsKeyDown(key);
    }

    void ClearAllKeys()
    {
        for (unsigned int i = 0; i < m_keys.size(); i++)
        {
            m_keys[i] = 0u;
        }
    }

    bool IsEqual(const KeyboardState& rhs)
    {
        bool result = true;

        for (unsigned int i = 0; i < m_keys.size(); i++)
        {
            result = result && m_keys[i] == rhs.m_keys[i];

            if (!result)
            {
                break;
            }
        }

        return result;
    }
};

class Keyboard
{
    private:
        static KeyboardState KbState;
    public :
        static KeyboardState GetState();
    
    static void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods); 
};

}

