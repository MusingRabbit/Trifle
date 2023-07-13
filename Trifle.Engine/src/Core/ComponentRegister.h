#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "ComponentArray.h"
#include <assert.h>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Types.h"

#include "../Util/Util.h"

namespace trifle
{

class ComponentRegister
{
  private:
    std::unordered_map<const char*, ComponentType> m_componentTypes;
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays;
    ComponentType m_componentTypeIndex;

  public:
    ComponentRegister()
    {
        m_componentTypes = {};
        m_componentArrays = {};
        m_componentTypeIndex = {};
    }

    ~ComponentRegister()
    {
        m_componentArrays.clear();
        m_componentTypes.clear();
        m_componentArrays.clear();
    }

    template <typename T>
    void RegisterComponent()
    {
        const char* typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) == m_componentTypes.end() && "Cannot register a component type more than once.");

        m_componentTypes.insert({typeName, m_componentTypeIndex});
        m_componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

        m_componentTypeIndex++;
    }

    std::vector<std::string> GetRegisteredComponents()
    {
        std::vector<std::string> result;

        for (const auto& pair : m_componentTypes)
        {
            std::string typeName(SysUtil::Demangle(pair.first));
            result.push_back(typeName);
        }

        return result;
    }

    template <typename T>
    ComponentType GetComponentType()
    {
        const char* typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");

        return m_componentTypes[typeName];
    }

    template <typename T>
    void AddComponent(unsigned int entityId, const T& component)
    {
        GetComponentArray<T>()->Insert(entityId, component);
    }

    template <typename T>
    void RemoveComponent(unsigned int entityId)
    {
        GetComponentArray<T>()->Remove(entityId);
    }

    template <typename T>
    T& GetComponent(unsigned int entityId)
    {
        return GetComponentArray<T>()->Get(entityId);
    }

    void EntityDestroyed(unsigned int entityId)
    {
        for (auto const& pair : m_componentArrays)
        {
            auto const& cmpArray = pair.second;
            cmpArray->EntityDestroyed(entityId);
        }
    }

    template <typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray()
    {
        const char* typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "No component of specified type is registered for provided entity Id.");

        return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
    }

    unsigned int GetCount()
    {
        unsigned int result = 0;

        for (auto const& pair : m_componentArrays)
        {
            auto const& cmpArray = pair.second;
            result += cmpArray->GetCount();
        }

        return result;
    }
};

} // namespace trifle

#endif // !COMPONENTMANAGER_H