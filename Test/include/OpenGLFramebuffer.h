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
			virtual void attach(GLenum attachment, OpenGLTexture* texture)									= 0;
			virtual void attach(GLenum attachment, GLenum internalFormat, GLsizei width, GLsizei height)	= 0;
			virtual bool isComplete(void)																	= 0;
			virtual void bind(void)																			= 0;
			virtual void unbind(void)																		= 0;

			// static member functions
			static OpenGLFramebuffer* CreateFramebuffer(void);
			static void DeleteFramebuffer(OpenGLFramebuffer* framebuffer);
	};
}

#endif /* _ORIGIN_FRAMEBUFFER_ */

