#ifndef TRIFLE_H
#define TRIFLE_H

#include "Components/Components.h"
#include "Core/Core.h"
#include "Data/Data.h"
#include "Entities/Entities.h"
#include "Factory/Factory.h"
#include "Graphics/Graphics.h"
#include "Systems/Systems.h"
#include "Util/Util.h"
#include "Input/Input.h"

#include <glm/glm.hpp>
#include <iostream>
#include <chrono>


namespace tfl
{
class Trifle
{
    private:
    std::shared_ptr<EntityManager> m_entityManager;
    std::shared_ptr<GameWindow> m_gameWindow;

    bool m_isInitialised = false;

    void RegisterComponents();
    void RegisterSystems();
    void InitSystems();
    void GameUpdateSystems(float dt);

    void RenderSystems(float dt);

    void GameWindow_OnResized(const EventArgs& e);

    public :
    Trifle();

    ~Trifle();

    void Init();

    int Run();

    template <typename T>
    void RegisterSystem()
    {
        static_assert(std::is_base_of<System, T>::value, "type parameter of this method must be of type <tfl::System>");
        
        std::shared_ptr<T> system = m_entityManager->RegisterSystem<T>(SystemContext(m_gameWindow, m_entityManager));
        
        if (m_isInitialised)
        {
            system->Init();
        }
    }

    template <typename T>
    void RegisterComponentType()
    {
        m_entityManager->RegisterComponent<T>();
    }

    template <typename T>
    std::shared_ptr<T> GetSystem()
    {
        return m_entityManager->GetSystem<T>();
    }

    template <typename T>
    T CreateEntity()
    {
        static_assert(std::is_base_of<Entity, T>::value, "type parameter of this method must be of type <tfl::Entity>");
        unsigned int entityId = Entity::entityManager->CreateEntity();
        Entity result(entityId);
        result.AddComponent<Transform>();
        return result;
    }
};



} // namespace tfl

#endif // !TRIFLE_H
