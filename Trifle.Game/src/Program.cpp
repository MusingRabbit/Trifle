#include "Program.h"

#include <glm/glm.hpp>
#include <iostream>
#include <chrono>

#include "Systems/Game.h"

/// @brief Constructor
Program::Program()
{
}

/// @brief Destructor
Program::~Program()
{
}

void Program::Init()
{
    m_engine.Init();

    m_engine.RegisterSystem<Game>();
}

/// @brief Starts main program loop
/// @return Error code. 0 indicates no Error
int Program::Run()
{
    return m_engine.Run();
}