#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>

namespace trifle
{
class System
{
  private:
    std::set<unsigned int> m_entityIds;

  protected:
    std::set<unsigned int> GetEntities();
    double m_totalElapsedTime;

  public:
    System();
    ~System();

    virtual void Init() = 0;
    virtual void Update(float dt);

    void AddEntity(unsigned int entityId);
    void RemoveEntity(unsigned int entityId);

    unsigned int GetEntityCount();
};
} // namespace trifle

#endif // !SYSTEM_H