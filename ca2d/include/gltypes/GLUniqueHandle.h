#ifndef RENDER_UTILS_GL_UNIQUE_HANDLE_H
#define RENDER_UTILS_GL_UNIQUE_HANDLE_H

#include <functional>
#include "../OpenGL.h"
#include <memory>

namespace rend
{
	#ifndef SH_DeleteFunc
		typedef std::function<void(GLuint)> SH_DeleteFunc;
	#endif

	class GLUniqueHandle
	{
	public:
		GLUniqueHandle(GLuint handle, SH_DeleteFunc deleteFunc);

        GLUniqueHandle(GLUniqueHandle&& other)
        {
            mDeleter = std::move(other.mDeleter);
            mUniqueHandle = std::move(other.mUniqueHandle);
        }

		operator GLuint() const;

	protected:
		void dispose(GLuint* i, SH_DeleteFunc deleteFunc);

	private:
		class Deleter
		{
		public:
			typedef GLuint pointer;

			Deleter();
			Deleter(SH_DeleteFunc deleteFunc);

			void operator()(GLuint shader);

			SH_DeleteFunc mDeleteFunc;
		};

		Deleter mDeleter;
		std::unique_ptr<GLuint, Deleter> mUniqueHandle;
	};
}

#endif /* RENDER_UTILS_GL_UNIQUE_HANDLE_H */