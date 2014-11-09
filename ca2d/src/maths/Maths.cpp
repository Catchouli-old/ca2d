#include "maths/Maths.h"

namespace ca2d
{
    /* Convert a 0..1 float to a uint8 */
    uint8_t u8fromfloat(float f)
    {
        // IEEE-754 floating point conversion to an int using type punning
        // See http://lolengine.net/blog/2011/3/20/understanding-fast-float-integer-conversions
        union { float f; uint32_t i; } u;
        u.f = 32768.0f + f * (255.0f / 256.0f);
        return (uint8_t)u.i;
    }

    /* Convert a uint8 to a 0..1 float */
    float floatfromu8(uint8_t i)
    {
        // IEEE-754 floating point conversion from an int using type punning
        // See http://lolengine.net/blog/2011/3/20/understanding-fast-float-integer-conversions
        union { float f; uint32_t i; } u;
        u.f = 32768.0f; u.i |= i;
        return (u.f - 32768.0f) * (256.0f / 255.0f);
    }
}