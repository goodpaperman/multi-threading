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

_declspec( dllimport ) BOOL TheFunction(); 
DWORD WINAPI ThreadFunc(LPVOID); 

int main(int argc, char* argv[])
{
    HANDLE hThrd; 
    DWORD dwThreadId; 

    for(int i=0; i<3; i++)
    {
        hThrd = CreateThread(NULL, 
            0, 
            ThreadFunc, 
            NULL, 
            0, 
            &dwThreadId); 
        
        if(hThrd)
            printf("\tThread %d launched\n", dwThreadId); 
    }

    WaitForSingleObject(hThrd, INFINITE); 
    CloseHandle(hThrd); 
    return 0;
}

/* 
 * Just call a function in the DLL and exit. 
 */
DWORD WINAPI ThreadFunc(LPVOID n)
{
    printf("\tThread running\n"); 
    TheFunction(); 
    return 0; 
}
