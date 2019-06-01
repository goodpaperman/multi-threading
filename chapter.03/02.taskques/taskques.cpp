// taskques.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/*
 * TaskQueS.c
 * 
 * Sample code for "Multithreading Applications in Win32" 
 * This is from Chapter 3, Listing 3-2
 * 
 * Call ThreadFunc NUM_TASKS times, using 
 * no more than THREAD_POOL_SIZE threads.
 * This version uses WaitForSingleObject, 
 * which gives a very suboptimal solution. 
 *
 * Build command: cl /MD TaskQues.c 
 */

#define WIN32_LEAN_AND_MEAN 
#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 
#include "MtVerify.h" 
#include <time.h> 

DWORD WINAPI ThreadFunc(LPVOID); 

#define THREAD_POOL_SIZE 3 
#define MAX_THREAD_INDEX THREAD_POOL_SIZE-1 
#define NUM_TASKS 6

int main(int argc, char* argv[])
{
    HANDLE hThrds[THREAD_POOL_SIZE]; 
    int slot = 0; 
    DWORD threadId; 
    int i; 
    DWORD exitCode; 

    /* i= 1 2 3 4 5 6 7 8 9
     * Start Thread X X X X X X
     * Wait on thread X X X X X X 
     */
    
    for(i=1; i<=NUM_TASKS; i++)
    {
        if(i > THREAD_POOL_SIZE)
        {
            WaitForSingleObject(hThrds[slot], INFINITE); 
            MTVERIFY(GetExitCodeThread(hThrds[slot], &exitCode)); 
            printf("thread #%d (slot %d) terminated\n", LOBYTE(exitCode), HIBYTE(exitCode)); 
            MTVERIFY(CloseHandle(hThrds[slot])); 
        }

        MTVERIFY(hThrds[slot] = CreateThread(NULL, 
            0, 
            ThreadFunc, 
            (LPVOID)MAKEWORD(i, slot), 
            0, 
            &threadId)); 

        printf("Launched thread #%d (slot %d)\n", i, slot); 
        if(++slot > MAX_THREAD_INDEX)
            slot = 0; 
    }

    for(slot = 0; slot < THREAD_POOL_SIZE; slot++)
    {
        WaitForSingleObject(hThrds[slot], INFINITE); 
        MTVERIFY(GetExitCodeThread(hThrds[slot], &exitCode)); 
        printf("thread #%d (slot %d) terminated\n", LOBYTE(exitCode), HIBYTE(exitCode)); 
        MTVERIFY(CloseHandle(hThrds[slot])); 
    }

    printf("All slots terminated\n"); 
    return EXIT_SUCCESS; 
}

/* 
 * This function just calls Sleep for 
 * a random amount of time, thereby 
 * simulating some tasks that takes time. 
 * 
 * The param "n" is the index into 
 * the handle array, kept for informational 
 * purposes.
 */
DWORD WINAPI ThreadFunc(LPVOID n)
{
    srand(GetTickCount()); 
    static int nWaits[NUM_TASKS] = 
    { 
        (rand() % 10) * 800 + 500,
        (rand() % 10) * 800 + 500,
        (rand() % 10) * 800 + 500,
        (rand() % 10) * 800 + 500,
        (rand() % 10) * 800 + 500,
        (rand() % 10) * 800 + 500,
    }; 
    
    static int i=0; 
    int nWait = nWaits[i++]; 
    Sleep(nWait); 
    printf("thread #%d (slot %d) idle after %d milisecond\n", LOBYTE(n), HIBYTE(n), nWait); 
    return (DWORD)n; 
}
