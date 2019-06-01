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

    //HMODULE dll_h = ::GetModuleHandle("entry.dll"); 
    //if(dll_h)
    //{
    //    DisableThreadLibraryCalls(dll_h); 
    //}

    hThrd = CreateThread(NULL, 
        0, 
        ThreadFunc, 
        NULL, 
        0, 
        &dwThreadId); 

    if(hThrd)
        printf("\tThread launched\n"); 

    //WaitForSingleObject(hThrd, INFINITE); 
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
