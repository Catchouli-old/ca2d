#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace ca2d
{
    struct Vertex2D
    {
        
        /* The position in world space of this vertex */
        glm::vec3 pos;

        /* The texture coordinates of this vertex */
        glm::vec2 uv;
    };
}