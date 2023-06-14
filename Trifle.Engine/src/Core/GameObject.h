#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "EntityService.h"
#include <memory>

namespace trifle
{
    class GameObject
    {
    private:
        std::shared_ptr<EntityService> m_service;
        unsigned int m_id;

    public:
        GameObject(std::shared_ptr<EntityService> entityService)
        {
            m_service = entityService;
            m_id = m_service->CreateEntity();
        }

        GameObject(GameObject &rhs)
        {
            m_service = rhs.m_service;
            m_id = rhs.m_id;
        }

        ~GameObject()
        {
            m_service->DestroyEntity(m_id);
        }

        unsigned int GetId()
        {
            return m_id;
        }

        template <typename T>
        void AddComponent()
        {
            T component;
            m_service->AddComponent<T>(m_id, component);
        }

        template <typename T>
        T GetComponent()
        {
            return m_service->GetComponent<T>(m_id);
        }

        template <typename T>
        void AddSystem()
        {
            return m_service->RegisterEntityOnSystem<T>(m_id);
        }

        template <typename T>
        T GetSystem()
        {
            return m_service->GetSystem<T>(m_id);
        }
    };

}

#endif // !GAMEOBJECT_H
