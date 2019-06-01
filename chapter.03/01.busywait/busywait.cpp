// busywait.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/*
 * BusyWait.c
 * 
 * Sample code for Multithreading Applications in Win32 
 * This is from Chapter 3, Listing 3-1 
 * 
 * Demonstrate the effect on performance 
 * of using a busy loop. First call the 
 * worker routine with just a function call 
 * to get a baseline performance reading, 
 * then create a second thread and a
 * busy loop. 
 * 
 * Build command: cl /MD busywait.c
 */

#define WIN32_LEAN_AND_MEAN 
#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 
#include <time.h> 
#include "MtVerify.h" 

DWORD WINAPI ThreadFunc(LPVOID); 

int main(int argc, char* argv[])
{
    HANDLE hThrd; 
    DWORD exitCode = 0; 
    DWORD threadId; 
    DWORD begin; 
    DWORD elapsed; 

    puts("Timing normal function call..."); 
    begin = GetTickCount(); 
    ThreadFunc(0); 
    elapsed = GetTickCount() - begin; 
    printf("Function call took: %d.%.03d seconds\n\n", 
        elapsed/1000, elapsed%1000); 

    puts("Timing thread + busy loop..."); 
    begin = GetTickCount(); 

    MTVERIFY( hThrd = CreateThread(NULL, 
        0, 
        ThreadFunc,
        (LPVOID)1, 
        0, 
        &threadId)); 

    /* This busy loop chews up lots of CPU time */
    for(;;)
    {
        GetExitCodeThread(hThrd, &exitCode); 
        if(exitCode != STILL_ACTIVE)
            break; 
    }

    elapsed = GetTickCount() - begin; 
    printf("Thread + busy loop took: %d.%.03d seconds\n\n", 
        elapsed/1000, elapsed%1000); 

    MTVERIFY( CloseHandle(hThrd)); 

    puts("Timing thread + wait..."); 
    begin = GetTickCount(); 
    MTVERIFY(hThrd = CreateThread(NULL, 
        0, 
        ThreadFunc, 
        (LPVOID)2, 
        0, 
        &threadId)); 

    if(::WaitForSingleObject(hThrd, INFINITE) == WAIT_OBJECT_0)
    {
        elapsed = GetTickCount() - begin; 
        printf("Thread + wait took: %d.%.03d seconds\n\n", 
            elapsed/1000, elapsed%1000); 

        MTVERIFY(CloseHandle(hThrd)); 
    }
    else 
        ; //MTASSERT(FALSE); 

    return EXIT_SUCCESS; 
}

/* 
 * Cute little busy work routine that computes the value 
 * of PI using probability. Highly dependent on having 
 * a good random number generator ( rand is iffy ) 
 */
DWORD WINAPI ThreadFunc(LPVOID n)
{
    int i; 
    int inside = 0; 
    double val; 
    
    UNREFERENCED_PARAMETER(n); 

    /* Seed the random-number generator */
    srand((unsigned)time(NULL)); 

    for(i=0; i<100000000/*0*/; i++)
    {
        double x = (double)(rand())/RAND_MAX; 
        double y = (double)(rand())/RAND_MAX; 
        if((x*x + y*y) <= 1.0)
            inside ++; 
    }

    val = (double)inside / i; 
    printf("PI = %.8g\n", val * 4); 
    return 0; 
}
