#ifndef RENDER_UTILS_GL_SHARED_HANDLE_H
#define RENDER_UTILS_GL_SHARED_HANDLE_H

#include <functional>
#include "../OpenGL.h"
#include <memory>

namespace rend
{
	#ifndef SH_DeleteFunc
		typedef std::function<void(GLuint)> SH_DeleteFunc;
	#endif

	class GLSharedHandle
	{
	public:
		GLSharedHandle(GLuint handle, SH_DeleteFunc deleteFunc);

		operator GLuint() const;

	protected:
		void dispose(GLuint* i, SH_DeleteFunc deleteFunc);

	private:
		std::shared_ptr<GLuint> mSharedHandle;
	};
}

#endif /* RENDER_UTILS_GL_SHARED_HANDLE_H */