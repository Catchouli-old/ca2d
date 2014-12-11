#pragma once

#include <coment/Component.h>

struct Radius
    : public coment::Component
{

    Radius(float v = 0.5f) : v(v) {}

    float v;

};
DECLARE_COMPONENT(Radius)