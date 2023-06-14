#include "System.h"

#include "../GameObjectManager.h"

namespace trifle
{
System::System()
{
    m_entityIds = {};
}

System::~System()
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

std::set<unsigned int> System::GetEntities()
{
    return m_entityIds;
}
} // namespace trifle