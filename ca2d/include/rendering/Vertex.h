#ifndef RENDER_UTILS_VERTEX_H
#define RENDER_UTILS_VERTEX_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "../gltypes/GLShaderProgram.h"

namespace rend
{
    struct Vertex
    {
        void bindPosition(GLint location);
        void bindPosition(GLShaderProgram& shader, const char* name, bool enable = true);
        static void bindPositionStatic(GLShaderProgram& shader, const char* name, bool enable = true);

        void bindNormal(GLint location);
        void bindNormal(GLShaderProgram& shader, const char* name, bool enable = true);
        static void bindNormalStatic(GLShaderProgram& shader, const char* name, bool enable = true);

        void bindTexCoords(GLint location);
        void bindTexCoords(GLShaderProgram& shader, const char* name, bool enable = true);
        static void bindTexCoordsStatic(GLShaderProgram& shader, const char* name, bool enable = true);

        glm::vec3 pos;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    inline void Vertex::bindPosition(GLShaderProgram& shader, const char* name, bool enable)
    {
        if (enable)
        {
            shader.enableAttribute(name);
        }

        GLuint location = shader.getAttributeLocation(name);

        glVertexAttribPointer(location, 3, GL_FLOAT, false, sizeof(Vertex), &pos);
    }

    inline void Vertex::bindPositionStatic(GLShaderProgram& shader, const char* name, bool enable)
    {
        if (enable)
        {
            shader.enableAttribute(name);
        }

        GLuint location = shader.getAttributeLocation(name);

        glVertexAttribPointer(location, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
    }

    inline void Vertex::bindPosition(GLint location)
    {
        glVertexAttribPointer(location, 3, GL_FLOAT, false, sizeof(Vertex), &pos);
    }

    inline void Vertex::bindNormal(GLShaderProgram& shader, const char* name, bool enable)
    {
        if (enable)
        {
            shader.enableAttribute(name);
        }

        GLuint location = shader.getAttributeLocation(name);

        glVertexAttribPointer(location, 3, GL_FLOAT, false, sizeof(Vertex), &normal);
    }

    inline void Vertex::bindNormalStatic(GLShaderProgram& shader, const char* name, bool enable)
    {
        if (enable)
        {
            shader.enableAttribute(name);
        }

        GLuint location = shader.getAttributeLocation(name);

        glVertexAttribPointer(location, 3, GL_FLOAT, false, sizeof(Vertex), (void*)12);
    }

    inline void Vertex::bindNormal(GLint location)
    {
        glVertexAttribPointer(location, 3, GL_FLOAT, false, sizeof(Vertex), &normal);
    }

    inline void Vertex::bindTexCoords(GLShaderProgram& shader, const char* name, bool enable)
    {
        if (enable)
        {
            shader.enableAttribute(name);
        }

        GLuint location = shader.getAttributeLocation(name);

        glVertexAttribPointer(location, 2, GL_FLOAT, false, sizeof(Vertex), &uv);
    }

    inline void Vertex::bindTexCoordsStatic(GLShaderProgram& shader, const char* name, bool enable)
    {
        if (enable)
        {
            shader.enableAttribute(name);
        }

        GLuint location = shader.getAttributeLocation(name);

        glVertexAttribPointer(location, 2, GL_FLOAT, false, sizeof(Vertex), (void*)24);
    }

    inline void Vertex::bindTexCoords(GLint location)
    {
        glVertexAttribPointer(location, 2, GL_FLOAT, false, sizeof(Vertex), &uv);
    }
}

#endif /* RENDER_UTILS_VERTEX_H */