#ifndef RENDER_UTILS_COLOUR_H
#define RENDER_UTILS_COLOUR_H

#include <glm/vec4.hpp>

#include "MathsUtils.h"

namespace rend
{
    /* Implements a colour class, inheriting from vec4 for built in operators and such */
    class Colour
        : public glm::vec4
    {
    public:

        /* Create colour from components - defaults to black */
        Colour(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);

        /* Convert colour to a 32-bit unsigned integer */
        uint32_t toUintARGB() const;

    private:

        /* The colour components in float format */
        float mR, mG, mB, mA;

    };

    /* Create colour from components - defaults to black */
    Colour::Colour(float r, float g, float b, float a)
        : mR(r), mG(g), mB(b), mA(a)
    {

    }

    /* Convert colour to a 32-bit unsigned integer */
    inline uint32_t Colour::toUintARGB() const
    {
        return u8fromfloat(mA) << 24
             | u8fromfloat(mR) << 16
             | u8fromfloat(mG) << 8
             | u8fromfloat(mB);
    }
}

#endif /* RENDER_UTILS_COLOUR_H */