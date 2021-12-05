// ---------------------------------------------------
// headers
// ---------------------------------------------------

#include <Origin.h>

// ---------------------------------------------------
// function declarations
// ---------------------------------------------------

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static void CreateOpenGLContext(HWND hwnd, HDC& hdc, HGLRC& hglrc);
static void DestroyOpenGLContext(HWND hwnd, HDC& hdc, HGLRC& hglrc);

// ---------------------------------------------------
// global data declarations
// ---------------------------------------------------

static origin::OriginApplication *app_instance = NULL;

// ---------------------------------------------------
// function implementation
// ---------------------------------------------------

int origin::OriginApplication::exec(HINSTANCE hInstance)
{
    // variable declaration
	WNDCLASSEX 	wndclass;

	HWND 		hwnd   = NULL;
	HDC    		hdc    = NULL;              
	HGLRC  		hglrc  = NULL;              

	MSG 		msg;
	TCHAR 		szAppName[] = TEXT("Origin");
	bool 		bRunLoop = true;

	// code
    app_instance = this; 

	// initialization of WNDCLASSEX
    wndclass.cbSize         = sizeof(WNDCLASSEX);                            	
    wndclass.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;            	
    wndclass.lpfnWndProc    = WndProc;                                       
    wndclass.cbClsExtra     = 0;                                             
    wndclass.cbWndExtra     = 0;                                             	
    wndclass.hInstance      = hInstance;                                     	
    wndclass.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(ORIGIN_ICON));		    
    wndclass.hCursor        = LoadCursor((HINSTANCE)NULL, IDC_ARROW);        
    wndclass.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);           
    wndclass.lpszClassName  = szAppName;                                     	
    wndclass.lpszMenuName   = NULL;                                          
    wndclass.hIconSm        = LoadIcon(hInstance, MAKEINTRESOURCE(ORIGIN_ICON));					

	// register above class
	RegisterClassEx(&wndclass);

    // create window
    hwnd = CreateWindowEx(WS_EX_APPWINDOW,                						         
            szAppName,                                    						
            TEXT("Origin Engine"),                                    	
            WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME | WS_CLIPCHILDREN |		
			WS_CLIPSIBLINGS | WS_VISIBLE,   
            0,                                       						
            0,                                       						
            GetSystemMetrics(SM_CXSCREEN),                                        
            GetSystemMetrics(SM_CYSCREEN),                                   
            (HWND)NULL,                                   					
            (HMENU)NULL,                                  						
            hInstance,                                    					
            (LPVOID)NULL);                                						    

	CreateOpenGLContext(hwnd, hdc, hglrc);
	initialize();
    imgui_initialize(hwnd);

    ShowWindow(hwnd, SW_MAXIMIZE);                 								
    SetForegroundWindow(hwnd);                  								
    SetFocus(hwnd);    

	// game loop
    while(bRunLoop)
    {   
        if(PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)           
            {
                bRunLoop = false;
            }
            else
            {
                TranslateMessage(&msg);          
                DispatchMessage(&msg);          
            }
        }
        else
        {
            render();   
			update();   
            imgui_render();

			SwapBuffers(hdc);                 
        }
    }

    imgui_uninitialize();
	uninitialize();
	DestroyOpenGLContext(hwnd, hdc, hglrc);
    OriginLogger::DeleteLogger();

    return ((int)msg.wParam);                    
}   

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// code
    app_instance->imgui_callback(hwnd, iMsg, wParam, lParam);

	switch (iMsg)
	{
		case WM_CREATE:
			break;

		case WM_ERASEBKGND:                      
            return (0);   

		case WM_SIZE:    
			app_instance->resize(LOWORD(lParam), HIWORD(lParam));                        
            break;

        case WM_KEYDOWN:                         
            switch(wParam)
            {                
                default:
                    break;
            }
            break;
        
        case WM_CLOSE:                          
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            app_instance->uninitialize();
            PostQuitMessage(0);
            break;

		default:
			break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

// ---------------------------------------------------
// static function implementation
// ---------------------------------------------------

static void CreateOpenGLContext(HWND hwnd, HDC& hdc, HGLRC& hglrc)
{
    // variable declarations
    PIXELFORMATDESCRIPTOR pfd;      
    int iPixelFormatIndex;          

    // code
    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR)); 
    pfd.nSize       = sizeof(PIXELFORMATDESCRIPTOR);                                
    pfd.nVersion    = 1;                                                          
    pfd.dwFlags     = PFD_DRAW_TO_WINDOW| PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;   
    pfd.iPixelType  = PFD_TYPE_RGBA;                                                
    pfd.cColorBits  = 32;                                                           
    pfd.cRedBits    = 8;                                                          
    pfd.cGreenBits  = 8;                                                           
    pfd.cBlueBits   = 8;                                                         
    pfd.cAlphaBits  = 8;                                                          
    pfd.cDepthBits  = 32;                                                       

    hdc = GetDC(hwnd);                    

    iPixelFormatIndex = ChoosePixelFormat(hdc, &pfd);
    if(iPixelFormatIndex == 0)
    {
        ORIGIN_FATAL("ChoosePixelFormat() failed");
        DestroyWindow(hwnd);
    }

    if(SetPixelFormat(hdc, iPixelFormatIndex, &pfd) == FALSE)
    {
        ORIGIN_FATAL("SetPixelFormat() failed");
        DestroyWindow(hwnd);
    }

    hglrc = wglCreateContext(hdc);
    if(hglrc == NULL)
    {
        ORIGIN_FATAL("wglCreateContext() failed");
        DestroyWindow(hwnd);
    }

    if(wglMakeCurrent(hdc, hglrc) == FALSE)
    {
        ORIGIN_FATAL("wglMakeCurrent() failed");
        DestroyWindow(hwnd);
    }

    GLenum glew_error = glewInit();
    if(glew_error != GLEW_OK)
    {
        ORIGIN_FATAL("glewInit() failed");
        DestroyWindow(hwnd);
    }
}

static void DestroyOpenGLContext(HWND hwnd, HDC& hdc, HGLRC& hglrc)
{
	// code
	if(wglGetCurrentContext() == hglrc)
    {
        wglMakeCurrent((HDC)NULL, (HGLRC)NULL);
    }

    if(hglrc)
    {
        wglDeleteContext(hglrc);
        hglrc = (HGLRC)NULL;
    }

    if(hdc)
    {
        ReleaseDC(hwnd, hdc);
        hdc = (HDC)NULL;
    }
}

