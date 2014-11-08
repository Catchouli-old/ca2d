#pragma once

#include <memory>
#include "../rendering/OpenGL.h"

namespace rend
{
    struct GLBufferDeleter
    {
        typedef GLuint pointer;

        void operator()(GLuint buffer)
        {
            glDeleteBuffers(1, &buffer);
        }
    };

    class GLBufferObject
    {
    public:
        GLBufferObject(const void* data = nullptr,
            size_t size = 0, GLenum usage = GL_STATIC_DRAW);

        operator GLuint() const;

    protected:
        GLuint createBuffer();

    private:
        std::unique_ptr<GLuint, GLBufferDeleter> mBuffer;
    };

    inline GLBufferObject::operator GLuint() const
    {
        return mBuffer.get();
    }

    inline GLuint GLBufferObject::createBuffer()
    {
        GLuint id;

        glGenBuffers(1, &id);

        return id;
    }

    inline GLBufferObject::GLBufferObject(const void* data, size_t size, GLenum usage)
        : mBuffer(createBuffer())
    {
        if (data != nullptr)
        {
            glBindBuffer(GL_ARRAY_BUFFER, mBuffer.get());
            glBufferData(GL_ARRAY_BUFFER, size, data, usage);
        }
    }
}