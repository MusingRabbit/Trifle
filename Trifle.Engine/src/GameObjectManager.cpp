#include "GameObjectManager.h"

#include "Core/EntityService.h"
#include "Core/GameObject.h"
#include "Components/Transform.h"

#include <unordered_map>
#include <memory>
namespace trifle
{

    GameObjectManager::GameObjectManager(/* args */)
    {
    }

    GameObjectManager::~GameObjectManager()
    {
    }

    void GameObjectManager::Init(std::shared_ptr<EntityService> entityService)
    {
        m_entityService = entityService;
    }

    std::shared_ptr<GameObject> GameObjectManager::CreateGameObject()
    {
        unsigned int entityId = m_entityService->CreateEntity();

        std::shared_ptr<GameObject> result = std::make_shared<GameObject>(m_entityService);

        result->AddComponent<Transform>();

        m_objs.insert({entityId, result});

        return result;
    }

    std::shared_ptr<GameObject> GameObjectManager::GetGameObject(unsigned int id)
    {
        std::shared_ptr<GameObject> result = m_objs[id];
        return result;
    }

    void GameObjectManager::DestroyGameObject(unsigned int id)
    {
        m_objs.erase(id);
        m_entityService->DestroyEntity(id);
    }
}