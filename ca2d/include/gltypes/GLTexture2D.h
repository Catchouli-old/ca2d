#pragma once

#include <memory>
#include "../rendering/OpenGL.h"

namespace ca2d
{
	class GLTexture2D
	{
	public:

        /** Creates a texture with the specified minification and magnification filters */
        GLTexture2D(GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR,
            GLint wrapU = GL_CLAMP_TO_EDGE, GLint wrapV = GL_CLAMP_TO_EDGE);

        /** Creates a texture from an image file with the specified min and mag filters */
        GLTexture2D(const char* filename, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR,
            GLint wrapU = GL_CLAMP_TO_EDGE, GLint wrapV = GL_CLAMP_TO_EDGE);

        /** Allocate device memory for a texture */
        void allocate(int width, int height, GLenum format = GL_RGBA);

        /** Load texture from an image file */
        bool load(const char* filename);

        /** Load texture from memory */
        bool load(uint32_t* buf, int width, int height);

        /** Whether or not this texture has been loaded */
		bool isLoaded();

        /** Bind this texture to the current texture unit */
		void bind() const;

        /** Bind this texture to a particular texture unit */
        void bind(GLenum unit) const;

        /** Return the width and height of this texture */
		int getWidth() const;
		int getHeight() const;

        /** Allow this object to be passed into opengl calls */
		operator GLuint() const;

	private:

        /** The smart pointer responsible for ownership of the opengl handle */
		std::shared_ptr<GLuint> mTextureId;

        /** The width and height of this texture */
		int mWidth, mHeight;

        /** Whether the texture is loaded */
		bool mLoaded;

        /** The minification, magnification, and wrap modes for this texture */
        GLint mMinFilter, mMagFilter, mWrapU, mWrapV;
	};

    /** Return the width of this texture */
    inline int GLTexture2D::getWidth() const
	{
		return mWidth;
	}

    /** Return the height of this texture */
    inline int GLTexture2D::getHeight() const
	{
		return mHeight;
	}

    /** Whether or not this texture has been loaded */
	inline bool GLTexture2D::isLoaded()
	{
		return mLoaded;
    }

    /** Allow this object to be passed into opengl calls */
    inline GLTexture2D::operator GLuint() const
    {
        return *mTextureId.get();
    }
}