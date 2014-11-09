#pragma once

#include <memory>
#include "../rendering/OpenGL.h"

namespace ca2d
{
    /* The deleter in charge of opengl buffer handles */
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

        /* Create an opengl buffer and optionally upload data to it */
        GLBufferObject(const void* data = nullptr,
            size_t size = 0, GLenum usage = GL_STATIC_DRAW);

        /* Upload data to the buffer */
        void upload(const void* data = nullptr,
            size_t size = 0, GLenum usage = GL_STATIC_DRAW);

        /* Allow objects of this class to be passed directly to opengl calls */
        operator GLuint() const;

    protected:

        /* Create a buffer and return an ID */
        static GLuint createBuffer();

    private:

        /* The smart pointer responsible for ownership of the buffer handle */
        std::unique_ptr<GLuint, GLBufferDeleter> mBuffer;

    };

    /* Allow objects of this class to be passed directly to opengl calls */
    inline GLBufferObject::operator GLuint() const
    {
        return mBuffer.get();
    }

    /* Create a buffer and return an ID */
    inline GLuint GLBufferObject::createBuffer()
    {
        GLuint id;

        glGenBuffers(1, &id);

        return id;
    }
}