#include "gltypes/GLTexture2D.h"

#include <stdio.h>

#ifdef EMSCRIPTEN
    #include <SDL_image.h>
#else
    #include <SDL/SDL_image.h>
#endif

namespace rend
{
	auto textureDeleter = [](GLuint *t)
	{
		glDeleteTextures(1, t);
		delete t;
	};

	GLTexture2D::GLTexture2D(GLint minFilter, GLint magFilter,
        GLint wrapU, GLint wrapV)
        : mLoaded(false), mMinFilter(minFilter), mMagFilter(magFilter),
        mWrapU(wrapU), mWrapV(wrapV)
	{
		GLuint textureId;
		glGenTextures(1, &textureId);
		mTextureId = std::shared_ptr<GLuint>(new GLuint(textureId), textureDeleter);
	}

    GLTexture2D::GLTexture2D(const char* filename, GLint minFilter, GLint magFilter,
        GLint wrapU, GLint wrapV)
        : mLoaded(false), mMinFilter(minFilter), mMagFilter(magFilter),
        mWrapU(wrapU), mWrapV(wrapV)
	{
		GLuint textureId;
		glGenTextures(1, &textureId);
		mTextureId = std::shared_ptr<GLuint>(new GLuint(textureId), textureDeleter);
		load(filename);
    }

    void GLTexture2D::allocate(int width, int height, GLenum format)
    {
        mLoaded = true;
        mWidth = width;
        mHeight = height;

        // Allocate texture
        glBindTexture(GL_TEXTURE_2D, *mTextureId.get());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mMinFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mMagFilter);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapU);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapV);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_RGBA, nullptr);
    }

	bool GLTexture2D::load(const char* filename)
	{
        // Load image
        SDL_Surface* image = IMG_Load(filename);

        // Get mode
        GLuint mode;

        if (image->format->BytesPerPixel == 3)
            mode = GL_RGB;
        else
            mode = GL_RGBA;
        
        // Generate texture
        glBindTexture(GL_TEXTURE_2D, *mTextureId.get());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mMinFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mMagFilter);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapU);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapV);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, mode, GL_UNSIGNED_BYTE, image->pixels);

        // Free image
        SDL_FreeSurface(image);

        return mLoaded;
	}

    bool GLTexture2D::load(uint32_t* buf, int width, int height)
    {
        mWidth = width;
        mHeight = height;

        // Generate texture
        glBindTexture(GL_TEXTURE_2D, *mTextureId.get());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mMinFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mMagFilter);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapU);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapV);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, buf);

        mLoaded = true;
        return true;
    }

	void GLTexture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, *mTextureId.get());
	}

	GLTexture2D::operator GLuint() const
	{
		return *mTextureId.get();
	}
}