#include "ComponentArray.h"

#include "Types.h"
#include <array>
#include <cassert>
#include <unordered_map>

template<typename T>
ComponentArray<T>::ComponentArray()
{

}

template<typename T>
ComponentArray<T>::~ComponentArray()
{

}

template <typename T>
ComponentArray<T>::ComponentArray(const ComponentArray<T>& rhs)
{
    m_componentArray = rhs.m_componentArray;
    m_entityToIndexMap = rhs.m_entityToIndexMap;
    m_indexToEntityMap = rhs.m_indexToEntityMap;
    m_size = rhs.m_size;
}

template<typename T>
void ComponentArray<T>::Insert(unsigned int entityId, T component)
{
    assert(m_entityToIndexMap.find(entityId) == m_entityToIndexMap.end() && "Duplicate addition of existing component. A component of the same type has already been mapped to this entity.");

    unsigned int newIndex = m_size;
    m_entityToIndexMap[entityId] = newIndex;
    m_indexToEntityMap[newIndex] = entityId;
    m_componentArray[newIndex] = component;
}

template<typename T>
void ComponentArray<T>::Remove(unsigned int entityId)
{
    assert(m_entityToIndexMap.find(entityId) != m_entityToIndexMap.end() && "Removing non-existent component.");

    // Copy element at the end into the deleted elements' place to maintain density
    unsigned long removedElementIndex = m_entityToIndexMap[entityId];
    unsigned long lastElementIndex = m_size - 1;

    m_componentArray[removedElementIndex] = m_componentArray[lastElementIndex];

    // Update entity mapping
    // Bring the entity Id from the back of the map to index that was just cleared.
    unsigned int entityIdToBump = m_indexToEntityMap[lastElementIndex];
    m_entityToIndexMap[entityIdToBump] = removedElementIndex;
    m_indexToEntityMap[removedElementIndex] = entityIdToBump;

    // Remove the mappings for the entity that has been removed.
    m_entityToIndexMap.erase(entityId);
    m_indexToEntityMap.erase(lastElementIndex);

    m_size--;
}

template<typename T>
T& ComponentArray<T>::Get(unsigned int entityId)
{
    assert(m_entityToIndexMap.find(entityId) != m_entityToIndexMap.end() && "Retrieving non-existent component.");
    return m_componentArray[entityId];
}

template<typename T>
void ComponentArray<T>::EntityDestroyed(unsigned int entityId) 
{
    if (m_entityToIndexMap.find(entityId) != m_entityToIndexMap.end())
    {
        Remove(entityId);
    }
}