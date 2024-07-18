#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>
#include <memory>

namespace tfl
{

  class EntityManager;
  class GameWindow;

  struct SystemContext
  {
    std::shared_ptr<GameWindow> gameWindow;
    std::shared_ptr<EntityManager> entityManager;

    SystemContext(){}

    SystemContext(std::shared_ptr<GameWindow> window, std::shared_ptr<EntityManager> manager)
    {
      gameWindow = window;
      entityManager = manager;
    }

    SystemContext(const SystemContext& rhs)
    {
      gameWindow = rhs.gameWindow;
      entityManager = rhs.entityManager;
    }

  };

  class System
  {
    private:
      unsigned int m_id;
      unsigned int m_orderNum;
      std::set<unsigned int> m_entityIds;

    protected:
      std::set<unsigned int> GetEntityIds();
      SystemContext Context;

      virtual void OnEntityAdded(unsigned int entityId) = 0;
      virtual void OnEntityRemoved(unsigned int entityId) = 0;

    public:
      static double TOTAL_ELAPSED_TIME;

      System(unsigned int id, const SystemContext& context);
      ~System();

      virtual void Init() = 0;
      virtual void Update();
      virtual void Draw();

      void AddEntity(unsigned int entityId);
      void RemoveEntity(unsigned int entityId);

      unsigned int GetEntityCount();

      static void UpdateTime(double dt);

      unsigned int GetId();
      void SetUpdateOrder(unsigned int orderNum);
      unsigned int GetUpdateOrder();
  };

} // namespace tfl

#endif // !SYSTEM_H
