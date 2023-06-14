#ifndef COMPONENT_ARRAY
#define COMPONENT_ARRAY

#include "Types.h"
#include <array>
#include <cassert>
#include <unordered_map>

namespace trifle
{
class IComponentArray
{
  public:
    virtual void EntityDestroyed(unsigned int entityId) = 0;
    virtual ~IComponentArray() = default;
    virtual unsigned int GetCount() = 0;
};

template <typename T>
class ComponentArray : public IComponentArray
{
  private:
    std::array<T, MAX_ENTITIES> m_componentArray;
    std::unordered_map<unsigned int, unsigned long> m_entityToIndexMap;
    std::unordered_map<unsigned long, unsigned int> m_indexToEntityMap;
    unsigned long m_size = 0;

  protected:
  public:
    /// @brief Constructor
    ComponentArray()
    {
        m_componentArray = {};
        m_entityToIndexMap = {};
        m_indexToEntityMap = {};
        m_size = 0;
    }

    ComponentArray(const ComponentArray<T>& rhs)
    {
        m_componentArray = rhs.m_componentArray;
        m_entityToIndexMap = rhs.m_entityToIndexMap;
        m_indexToEntityMap = rhs.m_indexToEntityMap;
        m_size = rhs.m_size;
    }

    ~ComponentArray()
    {
    }

    /// @brief Maps the entity to the component
    void Insert(unsigned int entityId, T component)
    {
        assert(
            m_entityToIndexMap.find(entityId) == m_entityToIndexMap.end() &&
            "Duplicate addition of existing component. A component of the same type has already been mapped to this entity.");

        unsigned int newIndex = m_size;
        m_entityToIndexMap[entityId] = newIndex;
        m_indexToEntityMap[newIndex] = entityId;
        m_componentArray[newIndex] = component;
        m_size++;
    }

    /// @brief Removes mapping between the entity and the component
    void Remove(unsigned int entityId)
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

    T& Get(unsigned int entityId)
    {
        const auto& pair = m_entityToIndexMap.find(entityId);
        assert(pair != m_entityToIndexMap.end() && "Retrieving non-existent component.");

        unsigned int idx = pair->second;
        return m_componentArray[idx];
    }

    void EntityDestroyed(unsigned int entityId) override
    {
        if (m_entityToIndexMap.find(entityId) != m_entityToIndexMap.end())
        {
            Remove(entityId);
        }
    }

    unsigned int GetCount() override
    {
        return m_size;
    }
};

} // namespace trifle
#endif // !COMPONENT_ARRAY
