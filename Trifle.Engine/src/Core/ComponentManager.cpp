#include "ComponentManager.h"

#include <memory>
#include <unordered_map>
#include "ComponentArray.h"
#include <assert.h>

ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
    m_componentArrays.clear();
    m_componentTypes.clear();
    m_componentArrays.clear();
}

template <typename T>
void ComponentManager::RegisterComponent()
{
    const char* typeName = typeid(T).name();

    assert(m_componentTypes.find(typeName) == m_componentTypes.end() && "Cannot register a component type more than once.");

    m_componentTypes.insert({typeName, m_componentTypeCount});
    m_componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

    m_componentTypeCount++;
}

template<typename T>
unsigned short ComponentManager::GetComponentTypeId()
{
    const char* typeName = typeid(T).name();

    assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");

    return m_componentTypes[typeName];
}

template<typename T>
void ComponentManager::AddComponent(unsigned int entityId, T component)
{
    GetComponentArray<T>()->Insert(entityId, component);
}

template<typename T>
void ComponentManager::RemoveComponent(unsigned int entityId)
{
    GetComponentArray<T>()->Remove(entityId);
}

template<typename T>
T& ComponentManager::GetComponent(unsigned int entityId)
{
    return GetComponentArray<T>()->Get(entityId);
}

void ComponentManager::EntityDestroyed(unsigned int entityId)
{
    for(auto const& pair : m_componentArrays)
    {
        auto const& component = pair.second;
        component->EntityDestroyed(entityId);
    }
}

template <typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray()
{
    const char* typeName = typeid(T).name();

    assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");

    return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
}