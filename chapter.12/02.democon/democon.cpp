// democon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>  
#include <stdio.h> 

DWORD WINAPI thread_proc(LPVOID param)
{
    //printf("enter thread_proc.\n"); 
    Sleep(1000); 
    //printf("leave thread_proc.\n"); 
    return 0; 
}

//extern void __declspec(dllimport) demo_func(); 

int main(int argc, char* argv[])
{
    char path[100] = { "demodll.dll" }; 
    //printf("Load DLL %s.\n", path); 
    HINSTANCE dll_h = LoadLibrary(path); 
    printf("dll_h = %d\n", dll_h); 

    //demo_func();  

    //printf("After Load\n"); 
    DWORD thread_id = 0; 
    HANDLE thread_h = CreateThread(
        NULL, 
        0, 
        thread_proc, 
        0, 
        0, 
        &thread_id); 

    WaitForSingleObject(thread_h, INFINITE); 

    //printf("Before Free\n"); 
    FreeLibrary(dll_h); 
	return 0;
}
