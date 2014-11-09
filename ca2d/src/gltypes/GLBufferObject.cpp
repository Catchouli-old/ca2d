#include <gltypes/GLBufferObject.h>

namespace ca2d
{
    /* Create an opengl buffer and optionally upload data to it */
    GLBufferObject::GLBufferObject(const void* data, size_t size, GLenum usage)
        : mBuffer(createBuffer())
    {
        if (data != nullptr)
        {
            upload(data, size, usage);
        }
    }

    /* Upload data to the buffer */
    void GLBufferObject::upload(const void* data, size_t size, GLenum usage)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mBuffer.get());
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    }
}