#include "System.h"

namespace trifle
{

System::System(EntityManager& manager) : m_entityManager(manager)
{
    m_entityIds = {};
}

System::~System()
{
}

void System::Update(float dt)
{
}

void System::AddEntity(unsigned int entityId)
{
    m_entityIds.insert(entityId);
}

void System::RemoveEntity(unsigned int entityId)
{
    m_entityIds.erase(entityId);
}

unsigned int System::GetEntityCount()
{
    return m_entityIds.size();
}

std::set<unsigned int> System::GetEntityIds()
{
    return m_entityIds;
}

EntityManager& System::GetEntityManager()
{
    return m_entityManager;
}

/* std::vector<std::shared_ptr<Entity>> System::GetEntities()
{
    std::vector<std::shared_ptr<Entity>> result;

    for (const auto& kvp : m_entities)
    {
        // result.insert(kvp.second);
    }

    return result;
} */

/* EntityController* System::GetEntityController()
{
    return m_entityController;
} */

/* void System::SetEntityController(EntityController* controller)
{
    m_entityController = controller;
}
 */

} // namespace trifle