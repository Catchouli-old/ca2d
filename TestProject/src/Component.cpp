#include "Component.h"

#include <iostream>
#include <sstream>

std::map<std::string, std::function<std::shared_ptr<Component>()>> constructorMap;

std::shared_ptr<Component> addComponent(const char* type)
{
    if (constructorMap.find(type) == constructorMap.end())
    {
        std::cerr << "Failed to find component type: " << type << std::endl;
        return std::shared_ptr<Component>();
    }

    return constructorMap.at(type)();
}

const char* componentTypeName(Component* cmp)
{
    return typeid(*cmp).name();
}