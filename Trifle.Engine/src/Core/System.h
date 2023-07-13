#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>
#include <memory>

namespace trifle
{

class EntityManager;

class System
{
  private:
    std::set<unsigned int> m_entityIds;
    EntityManager& m_entityManager;

  protected:
    std::set<unsigned int> GetEntityIds();
    EntityManager& GetEntityManager();

  public:
    static double TOTAL_ELAPSED_TIME;

    System(EntityManager& manager);
    ~System();

    virtual void Init() = 0;
    virtual void Update(float dt);

    void AddEntity(unsigned int entityId);
    void RemoveEntity(unsigned int entityId);

    unsigned int GetEntityCount();

    static void UpdateTime(double dt);
};

} // namespace trifle

#endif // !SYSTEM_H
