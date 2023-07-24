#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <unordered_map>
#include <memory>

namespace tfl
{
class ResourceManager
{
private:
    static std::unordered_map<unsigned char*, unsigned char*> resourceMap;
public:
    ResourceManager(/* args */);
    ~ResourceManager();

    unsigned char* GetResource(unsigned char* name);
    void AddResource(unsigned char* name, unsigned char* data);


};
}


#endif