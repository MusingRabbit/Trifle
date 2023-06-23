#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include "Core/EntityService.h"
#include "Core/GameObject.h"

#include <memory>
#include <unordered_map>

namespace trifle
{
class GameObjectManager
{
  private:
    std::shared_ptr<EntityService> m_entityService;
    std::unordered_map<unsigned int, std::shared_ptr<GameObject>> m_objs;

  public:
    GameObjectManager();
    ~GameObjectManager();

    void Init(std::shared_ptr<EntityService> entityService);

    std::shared_ptr<GameObject> CreateGameObject();
    std::shared_ptr<GameObject> GetGameObject(unsigned int entityId);
    void DestroyGameObject(unsigned int entityId);
};
} // namespace trifle

#endif // !GAMEOBJECTMANAGER_H