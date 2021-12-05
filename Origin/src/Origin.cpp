// ---------------------------------------------------
// headers
// ---------------------------------------------------

#include <windows.h>

// ---------------------------------------------------
// DLL entry point function
// ---------------------------------------------------

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
    //code
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;

        case DLL_PROCESS_DETACH:
            break;
    }

    return (TRUE);
}

