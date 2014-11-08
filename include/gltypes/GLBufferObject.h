#ifndef RENDER_UTILS_BUFFER_OBJECT_H
#define RENDER_UTILS_BUFFER_OBJECT_H

#include <memory>
#include "../OpenGL.h"

namespace rend
{
    class GLBufferObject
    {
    public:
        GLBufferObject();

        operator GLuint() const;

    protected:
        GLuint createBuffer();

    private:
        std::shared_ptr<GLuint> mSharedHandle;
    };

    inline GLBufferObject::operator GLuint() const
    {
        return *mSharedHandle;
    }

    inline void vboDeleter(GLuint vbo)
    {
        glDeleteBuffers(1, &vbo);
    };

    inline GLBufferObject::GLBufferObject()
        : mSharedHandle(new GLuint(createBuffer()), [&](GLuint* u) { vboDeleter(*u); delete u; })
    {

    }

    inline GLuint GLBufferObject::createBuffer()
    {
        GLuint id;

        glGenBuffers(1, &id);

        return id;
    }
}

#endif /* RENDER_UTILS_BUFFER_OBJECT_H */