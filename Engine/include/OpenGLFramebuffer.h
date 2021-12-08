#ifndef _ORIGIN_FRAMEBUFFER_
#define _ORIGIN_FRAMEBUFFER_

namespace origin
{
	// class declaration
	class OpenGLFramebuffer
	{
		public:
			// constructors
			OpenGLFramebuffer(void) { }

			// destructor
			virtual ~OpenGLFramebuffer(void) { }

			// non-static member functions
			virtual void bind(void) = 0;
			virtual void unbind(void) = 0;

			// static member functions

	};
}

#endif /* _ORIGIN_FRAMEBUFFER_ */

