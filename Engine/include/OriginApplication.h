#ifndef _ORIGIN_APPLICATION_
#define _ORIGIN_APPLICATION_

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace origin 
{
    // class declaration
    class OriginApplication
    {
        public:
            // constructors
            OriginApplication(void) { }

            // destructor
            virtual ~OriginApplication(void) { }

            // non-static member functions
            int exec(HINSTANCE hInstance);

            virtual void initialize(void)                   = 0;
            virtual void resize(int width, int height)      = 0;
            virtual void render(void)                       = 0;
            virtual void update(void)                       = 0;
            virtual void uninitialize(void)                 = 0;

            virtual void imgui_initialize(HWND hwnd) { /* empty */ }
            virtual void imgui_callback(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) { /* empty */ }
            virtual void imgui_render(void) { /* empty */ }
            virtual void imgui_uninitialize(void) { /* empty */ }
    };
}

#endif /* _ORIGIN_APPLICATION_ */
