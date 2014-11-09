#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>

namespace ca2d
{
    /* Convert a 0..1 float to a uint8 */
    uint8_t u8fromfloat(float f);

    /* Convert a uint8 to a 0..1 float */
    float floatfromu8(uint8_t i);

    struct col_t
    {
        float r, g, b;

        col_t() : r(0), g(0), b(0) {}
    };

    extern col_t i;

    inline void setValue(col_t value)
    {
        i = value;
    }

    inline col_t getValue()
    {
        return i;
    }

    inline col_t* getPointer()
    {
        return &i;
    }

    inline void newfunction()
    {
        std::cout << "New function\n";
    }
}