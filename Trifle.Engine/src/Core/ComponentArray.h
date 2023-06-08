#ifndef COMPONENT_ARRAY
#define COMPONENT_ARRAY

#include "Types.h"
#include <array>
#include <unordered_map>

class IComponentArray
{
public:
    virtual void EntityDestroyed(unsigned int entityId) = 0;
    virtual ~IComponentArray() = default;
};

template<typename T>
class ComponentArray : public IComponentArray
{
    private: 
    std::array<T, MAX_ENTITIES> m_componentArray;
    std::unordered_map<unsigned int, unsigned long> m_entityToIndexMap;
    std::unordered_map<unsigned long, unsigned int> m_indexToEntityMap;
    unsigned long m_size;
    protected:
    public:
    /// @brief Constructor
    ComponentArray();

    ComponentArray(const ComponentArray<T>& rhs);

    ~ComponentArray();

    /// @brief Maps the entity to the component
    void Insert(unsigned int entityId, T component);
    
    /// @brief Removes mapping between the entity and the component
    void Remove(unsigned int entityId);

    T& Get(unsigned int entityId);  

    void EntityDestroyed(unsigned int entityId) override;
};

#endif // !COMPONENT_ARRAY

