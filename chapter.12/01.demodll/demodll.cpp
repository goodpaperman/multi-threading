// demodll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "stdio.h" 

//BOOL APIENTRY DllMain( HANDLE hModule, 
//                       DWORD  ul_reason_for_call, 
//                       LPVOID lpReserved
//                     )
//{
//    return TRUE;
//}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved )  // reserved
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
         // Initialize once for each new process.
         // Return FALSE to fail DLL load.
            printf("DLL_PROCESS_ATTACH for 0x%x\n", hinstDLL);
            if(lpReserved == NULL)
                printf("use \"LoadLibrary\", lpReserved = %p\n", lpReserved); 
            else 
                printf("use \"comment lib(...)\", lpReserved = %p\n", lpReserved); 

            //return FALSE; 
            break;

        case DLL_THREAD_ATTACH:
         // Do thread-specific initialization.
            printf("DLL_THREAD_ATTACH for 0x%x\n", hinstDLL); 
            //ExitProcess(0);  
            break;

        case DLL_THREAD_DETACH:
         // Do thread-specific cleanup.
            printf("DLL_THREAD_DETACH for 0x%x\n", hinstDLL); 
            break;

        case DLL_PROCESS_DETACH:
         // Perform any necessary cleanup.
            printf("DLL_PROCESS_DETACH for 0x%x\n", hinstDLL); 
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

void __declspec(dllexport) demo_func()
{
}