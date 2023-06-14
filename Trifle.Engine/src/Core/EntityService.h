#ifndef ENTITYSERVICE_H
#define ENTITYSERVICE_H

#include "ComponentManager.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "SystemManager.h"
#include "Types.h"

#include <functional>
#include <memory>
#include <unordered_map>

namespace trifle
{
class EntityService
{
  private:
    std::unique_ptr<ComponentManager> m_componentManager;
    std::unique_ptr<EntityManager> m_entityManager;
    std::unique_ptr<EventManager> m_eventManager;
    std::unique_ptr<SystemManager> m_systemManager;

  public:
    EntityService()
    {
    }

    ~EntityService()
    {
    }

    void Init()
    {
        m_componentManager = std::make_unique<ComponentManager>();
        m_entityManager = std::make_unique<EntityManager>();
        m_eventManager = std::make_unique<EventManager>();
        m_systemManager = std::make_unique<SystemManager>();
    }

    unsigned int CreateEntity()
    {
        return m_entityManager->CreateEntity();
    }

    void DestroyEntity(unsigned int entityId)
    {
        m_entityManager->DestroyEntity(entityId);
        m_componentManager->EntityDestroyed(entityId);
        m_systemManager->EntityDestroyed(entityId);
    }

    template <typename T>
    void RegisterComponent()
    {
        m_componentManager->RegisterComponent<T>();
    }

    template <typename T>
    void AddComponent(unsigned int entityId, T component)
    {
        m_componentManager->AddComponent<T>(entityId, component);

        auto signature = m_entityManager->GetSignature(entityId);
        ComponentType cmpType = m_componentManager->GetComponentType<T>();
        signature.set(cmpType, true);
        m_entityManager->SetSignature(entityId, signature);

        m_systemManager->EntitySignatureChanged(entityId, signature);
    }

    template <typename T>
    void RemoveComponent(unsigned int entityId)
    {
        m_componentManager->RemoveComponent<T>(entityId);

        auto signature = m_entityManager->GetSignature(entityId);
        signature.set(m_componentManager->GetComponentType<T>(), false);
        m_entityManager->SetSignature(entityId, signature);

        m_systemManager->EntitySignatureChanged(entityId, signature);
    }

    template <typename T>
    T& GetComponent(unsigned int entityId)
    {
        return m_componentManager->GetComponent<T>(entityId);
    }

    template <typename T>
    void RegisterEntityOnSystem(unsigned int entityId)
    {
        std::shared_ptr<T> system = m_systemManager->GetSystem<T>();
        std::shared_ptr<System> result = std::static_pointer_cast<System>(system);
        result->AddEntity(entityId);
    }

    template <typename T>
    std::shared_ptr<T> GetSystem()
    {
        return m_systemManager->GetSystem<T>();
    }

    template <typename T>
    void RemoveEntityOnSystem(unsigned int entityId)
    {
        std::shared_ptr<System> system = m_systemManager->GetSystem<T>();
        system->RemoveEntity(entityId);
    }

    template <typename T>
    ComponentType GetComponentType()
    {
        return m_componentManager->GetComponentType<T>();
    }

    template <typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        return m_systemManager->RegisterSystem<T>();
    }

    template <typename T>
    void SetSystemSignature(Signature signature)
    {
        m_systemManager->SetSignature<T>(signature);
    }

    void AddEventListener(EventId eventId, std::function<void(Event&)> const& listener)
    {
        m_eventManager->AddListener(eventId, listener);
    }

    void SendEvent(Event& event)
    {
        m_eventManager->SendEvent(event);
    }

    void SendEvent(EventId eventId)
    {
        m_eventManager->SendEvent(eventId);
    }
};

} // namespace trifle

#endif // !ENTITYSERVICE_H