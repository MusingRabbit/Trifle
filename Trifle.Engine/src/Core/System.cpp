#include "System.h"

namespace tfl
{
double System::TOTAL_ELAPSED_TIME = 0;

System::System(unsigned int id, const SystemContext& context)
{
    m_id = id;
    m_entityIds = {};

    Context.entityManager = context.entityManager;
    Context.gameWindow = context.gameWindow;
}

System::~System()
{
}

void System::Update()
{
}

void System::Draw()
{
    
}

void System::AddEntity(unsigned int entityId)
{
    m_entityIds.insert(entityId);
    OnEntityAdded(entityId);
}

void System::RemoveEntity(unsigned int entityId)
{
    m_entityIds.erase(entityId);
    OnEntityRemoved(entityId);
}

unsigned int System::GetEntityCount()
{
    return m_entityIds.size();
}

void System::UpdateTime(double dt)
{
    System::TOTAL_ELAPSED_TIME += dt;
}

unsigned int System::GetId()
{
    return m_id;
}

void System::SetUpdateOrder(unsigned int orderNum)
{
    m_orderNum = orderNum;
}

unsigned int System::GetUpdateOrder()
{
    return m_orderNum;
}

std::set<unsigned int>& System::GetEntityIds()
{
    return m_entityIds;
}

void System::OnEntityAdded(unsigned int entityId)
{
}

void System::OnEntityRemoved(unsigned int entityId)
{
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

} // namespace tfl