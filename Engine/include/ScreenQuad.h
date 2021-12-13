#pragma once 

namespace origin
{
	// class declarations
	class ScreenQuad
	{
		public:
			// constructors
			ScreenQuad(void) { }

			// destructor
			virtual ~ScreenQuad(void) { }

			// non-static member functions
			virtual void renderToScreen(OpenGLTexture* texture) = 0;

			// static member functions
			static ScreenQuad* CreateScreenQuad(void);
			static void DeleteScreenQuad(ScreenQuad* screenQuad);
	};
}

