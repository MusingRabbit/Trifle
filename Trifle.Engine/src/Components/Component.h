#ifndef COMPONENT_H
#define COMPONENT_H

 #include <stdint.h>

class Component
{
private:
    unsigned int m_id;
    bool m_enabled;

public:
    Component();
    ~Component();

    void Update();
    void Initialise();
};




#endif // !COMPONENT_H
