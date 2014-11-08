#pragma once

#include <memory>
#include "../rendering/OpenGL.h"

namespace rend
{
	class GLTexture2D
	{
	public:
        GLTexture2D(GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR,
            GLint wrapU = GL_CLAMP_TO_EDGE, GLint wrapV = GL_CLAMP_TO_EDGE);
        GLTexture2D(const char* filename, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR,
            GLint wrapU = GL_CLAMP_TO_EDGE, GLint wrapV = GL_CLAMP_TO_EDGE);

        void allocate(int width, int height, GLenum format = GL_RGBA);

        bool load(const char* filename);
        bool load(uint32_t* buf, int width, int height);

		inline bool isLoaded();

		void bind() const;

		inline int getWidth() const;
		inline int getHeight() const;

		operator GLuint() const;

	private:
		std::shared_ptr<GLuint> mTextureId;

		int mWidth, mHeight;

		bool mLoaded;

        GLint mMinFilter, mMagFilter, mWrapU, mWrapV;
	};

	int GLTexture2D::getWidth() const
	{
		return mWidth;
	}

	int GLTexture2D::getHeight() const
	{
		return mHeight;
	}

	bool GLTexture2D::isLoaded()
	{
		return mLoaded;
	}
}