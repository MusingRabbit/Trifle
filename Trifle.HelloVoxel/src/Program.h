#ifndef PROGRAM_H
#define PROGRAM_H

#include <memory>
#include <trifle.h>

using namespace tfl;

class Program
{
  private:
    tfl::Trifle m_engine;
    
  protected:
  public:
    Program();

    void Init();

    int Run();

    virtual ~Program();
};

#endif // !PROGRAM_H