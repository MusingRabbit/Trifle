#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <memory>
#include <unordered_map>
#include "ComponentArray.h"

class ComponentManager
{
    private : 
    std::unordered_map<const char*, unsigned short> m_componentTypes;
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays;
    unsigned short m_componentTypeCount;

    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray();

    public :
    ComponentManager();
    ~ComponentManager();

    template<typename T>
    void RegisterComponent();

    template<typename T>
	unsigned short GetComponentTypeId();

    template<typename T>
	void AddComponent(unsigned int entityId, T component);
    
    template<typename T>
    void RemoveComponent(unsigned int entityId);

    template<typename T>
    T& GetComponent(unsigned int entityId);

    void EntityDestroyed(unsigned int entityId);
};

#endif // !COMPONENTMANAGER_H