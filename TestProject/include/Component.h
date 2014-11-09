#pragma once

#include <map>
#include <memory>
#include <functional>

#define DEFINE_COMPONENT(x, y) constructorMap[x] = []() { return std::make_shared<y>(); };

struct Component
{
    virtual ~Component() {}
};

extern std::map<std::string, std::function<std::shared_ptr<Component>()>> constructorMap;

std::shared_ptr<Component> addComponent(const char* type);

struct TransformComponent
    : public Component
{
    float x, y;
};

struct ColourComponent
    : public Component
{
    float r, g, b;
};

const char* componentTypeName(Component* cmp);