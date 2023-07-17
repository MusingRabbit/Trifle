#ifndef ENTITY_H
#define ENTITY_H

#include "EntityManager.h"
#include "../Components/EntityData.h"
#include <memory>
#include <stdexcept>

namespace tfl
{
class Entity
{
  private:
    inline static std::shared_ptr<EntityManager> entityManager;

    unsigned int m_id = -1;

  public:
    static void Init(std::shared_ptr<EntityManager> manager);

    static void InitialisationCheck();

    static Entity Create();

    static void Destroy(unsigned int entityId);

    Entity(unsigned int entityId);

    Entity(const Entity& rhs);

    Entity();

    ~Entity();

    void Register();

    unsigned int GetId();

    void SetId(unsigned int entityId);

    template <typename T>
    void AddComponent()
    {
        Entity::InitialisationCheck();
        T component;
        Entity::entityManager->AddComponent<T>(m_id, component);
    }

    template <typename T>
    void AddComponent(T component)
    {
        Entity::InitialisationCheck();
        Entity::entityManager->AddComponent<T>(m_id, component);
    }

    template <typename T>
    T& GetComponent()
    {
        Entity::InitialisationCheck();
        return Entity::entityManager->GetComponent<T>(m_id);
    }

    template <typename T>
    void AddSystem()
    {
        Entity::InitialisationCheck();
        return Entity::entityManager->RegisterEntityOnSystem<T>(m_id);
    }

    void Destroy();

    bool IsEnabled();

    void SetIsEnabled(bool value);
};

} // namespace tfl

#endif // !ENTITY_H
