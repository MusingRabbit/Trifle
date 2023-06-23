#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "System.h"
#include "Types.h"
#include <any>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <unordered_map>

namespace trifle
{
class SystemManager
{
  private:
    std::unordered_map<const char*, Signature> m_signatures;
    std::unordered_map<const char*, std::shared_ptr<System>> m_systems;

  public:
    SystemManager()
    {
        // m_signatures = {};
        // m_systems = {};
    }
    ~SystemManager()
    {
    }

    template <typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        static_assert(std::is_base_of<System, T>::value,
                      "type parameter of this method must be of type <trifle::System>");

        const char* typeName = typeid(T).name();

        assert(m_systems.find(typeName) == m_systems.end() && "Cannot register a system type more than once.");

        auto system = std::make_shared<T>();
        m_systems.insert({typeName, system});
        return system;
    }

    template <typename T>
    std::shared_ptr<T> GetSystem()
    {
        static_assert(std::is_base_of<System, T>::value,
                      "type parameter of this method must be of type <trifle::System>");

        for (auto const& pair : m_systems)
        {
            auto const system = pair.second;
            return std::static_pointer_cast<T>(system);
        }

        throw std::runtime_error("The specified system for the provided entity Id could not be found");
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
        for (auto const& pair : m_systems)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = m_signatures[type];

            if ((entitySignature & systemSignature) == systemSignature)
            {
                system->AddEntity(entityId);
            }
            else
            {
                system->RemoveEntity(entityId);
            }
        }
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
} // namespace trifle

#endif // !SYSTEMMANAGER_H