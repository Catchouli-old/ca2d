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
}