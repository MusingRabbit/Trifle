#ifndef PROGRAM_H
#define PROGRAM_H

#include <memory>
#include <trifle.h>

using namespace trifle;

class Program
{
  private:
    std::shared_ptr<EntityManager> m_entityManager;
    std::shared_ptr<GLGameWindow> m_gameWindow;

    void RegisterComponents();
    void RegisterSystems();
    void InitSystems();
    void GameUpdateSystems(float dt);

  protected:
  public:
    Program();

    void Init();

    int Run();

    virtual ~Program();
};

#endif // !PROGRAM_H