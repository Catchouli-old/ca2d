#pragma once

#include <glm/vec4.hpp>

#include "Maths.h"

namespace ca2d
{
    /* Implements a colour class, inheriting from vec4 for built in operators and such */
    struct Colour
        : public glm::vec4
    {

        /* Create default colour (black) */
        Colour();

        /* Create colour from components */
        Colour(float r, float g, float b, float a = 0.0f);

        /* Convert colour to a 32-bit unsigned integer */
        uint32_t toUintARGB() const;

    };

    /* Convert colour to a 32-bit unsigned integer */
    inline uint32_t Colour::toUintARGB() const
    {
        return u8fromfloat(a) << 24
             | u8fromfloat(r) << 16
             | u8fromfloat(g) << 8
             | u8fromfloat(b);
    }
}