#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "System.h"
#include "Types.h"
#include <any>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>

namespace tfl
{
class EntityManager;

class SystemRegister
{
  private:
    unsigned int m_systemCounter;
    std::unordered_map<const char*, Signature> m_signatures;
    std::unordered_map<const char*, std::shared_ptr<System>> m_systems;

  public:
    SystemRegister()
    {
        // m_signatures = {};
        // m_systems = {};
    }

    ~SystemRegister()
    {
    }

    template <typename T>
    std::shared_ptr<T> RegisterSystem(SystemContext context)
    {
        static_assert(std::is_base_of<System, T>::value, "type parameter of this method must be of type <tfl::System>");

        const char* typeName = typeid(T).name();

        assert(m_systems.find(typeName) == m_systems.end() && "Cannot register a system type more than once.");

        std::shared_ptr<T> system = std::make_shared<T>(m_systemCounter++, context);
        m_systems.insert({typeName, system});
        return system;
    }

    template <typename T>
    std::shared_ptr<T> GetSystem()
    {
        static_assert(std::is_base_of<System, T>::value, "type parameter of this method must be of type <tfl::System>");

        const char* typeName = typeid(T).name();

        const auto result = m_systems.find(typeName);

        if (result == m_systems.end())
        {
            throw std::runtime_error("The specified system for the provided entity Id could not be found");
        }

        return std::static_pointer_cast<T>(result->second);
    }
    
    std::vector<std::shared_ptr<System>> GetSystems()
    {
        std::vector<std::shared_ptr<System>> result;

        for (auto& pair : m_systems)
        {
            result.push_back(pair.second);
        }

        std::sort(result.begin(), result.end(), [](std::shared_ptr<System> lhs, std::shared_ptr<System> rhs){  return lhs->GetUpdateOrder() < rhs->GetUpdateOrder(); });

        return result;
    }

    template <typename T>
    void SetSignature(Signature signature)
    {
        const char* typeName = typeid(T).name();

        assert(m_systems.find(typeName) != m_systems.end() && "System used before registered.");

        m_signatures.insert({typeName, signature});
    }

    void EntitySignatureChanged(unsigned int entityId, Signature entitySignature)
    {
        // for (auto const& pair : m_systems)
        //{
        //     auto const& type = pair.first;
        //     auto const& system = pair.second;
        //     auto const& systemSignature = m_signatures[type];
        //
        //    if ((entitySignature & systemSignature) == systemSignature)
        //    {
        //        system->AddEntity(entityId);
        //    }
        //    else
        //    {
        //        system->RemoveEntity(entityId);
        //    }
        //}
    }

    void EntityDestroyed(unsigned int entityId)
    {
        for (auto const& pair : m_systems)
        {
            auto const& system = pair.second;
            system->RemoveEntity(entityId);
        }
    }
};
} // namespace tfl

#endif // !SYSTEMMANAGER_H
