#include "maths/Colour.h"

namespace ca2d
{
    /* Create default colour (black) */
    Colour::Colour()
    {
        // The default constructor of glm::vec4 takes care of this
    }

    /* Create colour from components */
    Colour::Colour(float r, float g, float b, float a)
        : glm::vec4(r, g, b, a)
    {

    }
}