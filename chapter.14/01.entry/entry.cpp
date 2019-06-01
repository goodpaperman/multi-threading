// entry.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

/* 
 * Entry.cpp 
 * 
 * Sample code for "Multithreading Application in Win32" 
 * This is from Chapter 14, Listing 14-1 
 * 
 * Demonstrate a very simple DLL that prints 
 * status message when its functions are called 
 * a provides a single entry point called 
 * TheFunction() for test purposes. 
 */


#define WIN32_MEAN_AND_LEAN
#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    DWORD tid = GetCurrentThreadId(); 
    // Why are we being called? 
    switch( ul_reason_for_call )
    {
    case DLL_PROCESS_ATTACH: 
        //DisableThreadLibraryCalls((HMODULE)hModule); 
        printf("DLL:\tProcess attach (tid = %d)\n", tid); 
        break; 
    case DLL_THREAD_ATTACH:
        printf("DLL:\tThread attach (tid = %d)\n", tid); 
        break; 
    case DLL_THREAD_DETACH:
        printf("DLL:\tThread detach (tid = %d)\n", tid); 
        break; 
    case DLL_PROCESS_DETACH:
        printf("DLL:\tProcess detach (tid = %d)\n", tid); 
        break; 
    }

    return TRUE;
}

_declspec( dllexport ) BOOL TheFunction()
{
    printf("DLL:\tTheFunction() called\n"); 
    return TRUE; 
}

