// numbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/* 
 * Numbers.c
 * 
 * Sample code for "Multithreading Applications in Win32" 
 * This is from Chapter 2, Listing 2-1 
 * 
 * Starts five threads and gives visible feedback 
 * of these threads running by printing a number 
 * passed in from the primary thread.
 * 
 */

#define WIN32_LEAN_AND_MEAN 
#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 

DWORD WINAPI ThreadProc(LPVOID); 

int main(int argc, char* argv[])
{
    HANDLE hThrd; 
    DWORD threadId; 
    int i; 

    for(i=0; i<5; i++)
    {
        hThrd = CreateThread(NULL,
            0, 
            ThreadProc, 
            (LPVOID)i, 
            0, 
            &threadId); 
        
        if(hThrd)
        {
            printf("Thread launched %d\n", i); 
            CloseHandle(hThrd); 
        }
        
        for(int j=0; j<100000; j++); 

    }

    // Wait for the threads to complete.
    // We'll see a better way of doing this later.
    Sleep(2000); 

    char c; 
    scanf("%c", &c); 
    return EXIT_SUCCESS; 
}

DWORD WINAPI ThreadProc(LPVOID n)
{
    int i; 
    for(i=0; i<10; i++)
        printf("%d%d%d%d%d%d%d%d\n", n, n, n, n, n, n, n, n); 
    return 0; 
}
