#ifndef RENDER_UTILS_MATHS_UTILS_H
#define RENDER_UTILS_MATHS_UTILS_H

#include <algorithm>
#include <cstdint>

namespace rend
{
    /* Definitions */

    /* Clamp a value */
    template <typename T>
    const T& clamp(const T& a, const T& min, const T& max);

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

    /* Inline implementations */

    /* Clamp a value */
    template <typename T>
    inline const T& clamp(const T& a, const T& min, const T& max)
    {
        return std::max(min, std::min(max, a));
    }
}

#endif /* RENDER_UTILS_MATHS_UTILS_H */