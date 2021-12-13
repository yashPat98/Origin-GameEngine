#pragma once

namespace origin
{
	// class declaration
	class OriginMSAA
	{
		public:
			// constructors
			OriginMSAA(void) { }

			// destructor
			virtual ~OriginMSAA(void) { }

			// non-static member functions
			virtual void bind(void)				= 0;
			virtual void unbind(void)			= 0;
			virtual GLuint screenTexture(void)	= 0;

			// static member functions
			static OriginMSAA* CreateMSAA(void);
			static void DeleteMSAA(OriginMSAA* msaa);
	};
}
