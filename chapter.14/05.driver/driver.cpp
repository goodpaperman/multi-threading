// driver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/* 
 * Main1.cpp
 * 
 * Sample code for "Multithreading Application in Win32" 
 * This is from Chapter 14, Listing 14-2 
 * 
 * Driver to load the simple DLL, create a 
 * thread, call a function in the DLL, and exit. 
 */

#define WIN32_MEAN_AND_LEAN 
#include <windows.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include "MtVerify.h"

typedef _declspec( dllimport ) BOOL (*THEFUNCTION)(); 
THEFUNCTION pTheFunc; 
DWORD WINAPI ThreadFunc(LPVOID); 

int main(int argc, char* argv[])
{
    HANDLE hThrd; 
    DWORD dwThreadId; 

    hThrd = CreateThread(NULL, 
        0, 
        ThreadFunc, 
        NULL, 
        0, 
        &dwThreadId); 

    printf("little thread id: %d\n", dwThreadId); 
    dwThreadId = GetCurrentThreadId(); 
    printf("main thread id: %d\n", dwThreadId); 

    MTVERIFY(hThrd); 
    if(hThrd)
        printf("\tThread launched\n"); 


    MTVERIFY(WaitForSingleObject(hThrd, INFINITE) == WAIT_OBJECT_0); 
    MTVERIFY(CloseHandle(hThrd));
    return 0;
}

/* 
 * Just call a function in the DLL and exit. 
 */
DWORD WINAPI ThreadFunc(LPVOID n)
{
    printf("\tThread running\n");
    printf("\tCalling LoadLibrary()\n"); 

    HINSTANCE hinstlib; 
    hinstlib = LoadLibrary("entry.dll"); 
    if(hinstlib == NULL)
    {
        fprintf(stderr, "LoadLibrary failed, could not find entry.dll"); 
        return 1; 
    }

    pTheFunc = (THEFUNCTION)GetProcAddress(hinstlib, "?TheFunction@@YAHXZ"); 
	if (pTheFunc == NULL)
	{
		fprintf(stderr, "\nGetProcAddress failed. There is probably a\n");
		fprintf(stderr, "calling convention or parameter mismatch.\n\n");
		return 1;
	}

    pTheFunc(); 
    
    printf("\tCalling FreeLibrary()\n"); 
    FreeLibrary(hinstlib);     
    return 0; 
}
