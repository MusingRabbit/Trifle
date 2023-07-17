#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "ComponentRegister.h"
#include "EntityRegister.h"
#include "EventRegister.h"
#include "SystemRegister.h"
#include "System.h"
#include "Types.h"

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace tfl
{

/// @brief Class for managing entities
class EntityManager
{
  private:
    std::unique_ptr<ComponentRegister> m_componentRegister;
    std::unique_ptr<EntityRegister> m_entityRegister;
    std::unique_ptr<SystemRegister> m_systemRegister;

    void RegisterComponents();

    void RegisterSystems();

  public:
    EntityManager();

    ~EntityManager();

    void Init();

    unsigned int CreateEntity();

    void DestroyEntity(unsigned int entityId);

    template <typename T>
    void RegisterComponent()
    {
        m_componentRegister->RegisterComponent<T>();
    }

    template <typename T>
    void AddComponent(unsigned int entityId, T component)
    {
        m_componentRegister->AddComponent<T>(entityId, component);

        auto signature = m_entityRegister->GetSignature(entityId);
        ComponentType cmpType = m_componentRegister->GetComponentType<T>();
        signature.set(cmpType, true);
        m_entityRegister->SetSignature(entityId, signature);

        m_systemRegister->EntitySignatureChanged(entityId, signature);
    }

    template <typename T>
    void RemoveComponent(unsigned int entityId)
    {
        m_componentRegister->RemoveComponent<T>(entityId);

        auto signature = m_entityRegister->GetSignature(entityId);
        signature.set(m_componentRegister->GetComponentType<T>(), false);
        m_entityRegister->SetSignature(entityId, signature);

        m_systemRegister->EntitySignatureChanged(entityId, signature);
    }

    template <typename T>
    T& GetComponent(unsigned int entityId)
    {
        return m_componentRegister->GetComponent<T>(entityId);
    }

    template <typename T>
    void RegisterEntityOnSystem(unsigned int entityId)
    {
        std::shared_ptr<T> system = m_systemRegister->GetSystem<T>();
        std::shared_ptr<System> result = std::static_pointer_cast<System>(system);
        result->AddEntity(entityId);
    }

    template <typename T>
    std::shared_ptr<T> GetSystem()
    {
        return m_systemRegister->GetSystem<T>();
    }

    std::vector<std::shared_ptr<System>> GetSystems();

    template <typename T>
    void RemoveEntityOnSystem(unsigned int entityId)
    {
        std::shared_ptr<System> system = m_systemRegister->GetSystem<T>();
        system->RemoveEntity(entityId);
    }

    template <typename T>
    ComponentType GetComponentType()
    {
        return m_componentRegister->GetComponentType<T>();
    }

    template <typename T>
    std::shared_ptr<T> RegisterSystem(SystemContext ctx)
    {
        return m_systemRegister->RegisterSystem<T>(ctx);
    }

    template <typename T>
    void SetSystemSignature(Signature signature)
    {
        m_systemRegister->SetSignature<T>(signature);
    }
};

} // namespace tfl

#endif // !ENTITYMANAGER_H