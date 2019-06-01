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

static DWORD gdwTlsSlot; 
_declspec(thread) DWORD gThreadId; 

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
        gdwTlsSlot = TlsAlloc(); 
        if(gdwTlsSlot == 0xFFFFFFFF)
            return FALSE; 
        // fall through to handle thread attach too
    case DLL_THREAD_ATTACH:
        if(TlsSetValue(gdwTlsSlot, (LPVOID)tid) == FALSE)
            printf("TlsSetValue error.\n"); 

        gThreadId = tid*2; 
        break; 
    case DLL_THREAD_DETACH:
        break; 
    case DLL_PROCESS_DETACH:
        TlsFree(gdwTlsSlot); 
        break; 
    }

    return TRUE;
}

_declspec( dllexport ) BOOL TheFunction()
{
    printf("DLL:\tTheFunction() called\n"); 
    DWORD tid = (DWORD)TlsGetValue(gdwTlsSlot); 
    printf("DLL:\ttid = %d\n", tid); 
    printf("DLL:\ttid*2 = %d\n", gThreadId); 
    return TRUE; 
}

