#include "gltypes/GLSharedHandle.h"

namespace rend
{
	GLSharedHandle::GLSharedHandle(GLuint handle, SH_DeleteFunc deleteFunc)
	{
		std::function<void(GLuint*)> func =
			std::bind(&GLSharedHandle::dispose, this, std::placeholders::_1, deleteFunc);

		mSharedHandle = std::shared_ptr<GLuint>(new GLuint(handle), func);
	}

	GLSharedHandle::operator GLuint() const
	{
		return *mSharedHandle.get();
	}

	void GLSharedHandle::dispose(GLuint* i, SH_DeleteFunc deleteFunc)
	{
		// Dispose i
		deleteFunc(*i);

		// Delete i
		delete i;
	}
}