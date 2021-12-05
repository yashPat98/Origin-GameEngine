#ifndef _ORIGIN_GUI_
#define _ORIGIN_GUI_

namespace origin
{
	// class declaration
	class OriginGUI
	{
		public:
			// constructors
			OriginGUI(void) { }

			// destructor
			virtual ~OriginGUI(void) { }

			// non-static member functions
			virtual void imgui_initialize(void)		= 0;
			virtual void imgui_render(void)			= 0;
			virtual void imgui_callback(void)		= 0;
			virtual void imgui_uninitialize(void)	= 0;

			friend class OriginApplication;
	};
}

#endif /* _ORIGIN_GUI_*/
