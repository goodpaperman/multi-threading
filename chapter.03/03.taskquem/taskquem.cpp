// taskquem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/* 
 * TaskQueM.c
 * 
 * Sample code for "Multithreading Applications in Win32" 
 * This is from Chapter 3, Listing 3-3 
 * 
 * Call ThreadFunc NUM_TASKS times, using 
 * no more than THREAD_POOL_SIZE threads. 
 * This version uses WaitForMultipleObjects 
 * to provide a more optimal solution.
 * 
 * Build command: cl /MD TaskQueM.c
 */

#define WIN32_LEAN_AND_MEAN 
#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 
#include "MtVerify.h" 

DWORD WINAPI ThreadFunc(LPVOID); 

#define THREAD_POOL_SIZE 3 
#define MAX_THREAD_INDEX THREAD_POOL_SIZE - 1 
#define NUM_TASKS 6 

int main(int argc, char* argv[])
{
    HANDLE hThrds[THREAD_POOL_SIZE]; 
    int slot = 0; 
    DWORD threadId; 
    int i; 
    DWORD rc; 
    DWORD exitCode; 

    for(i=1; i<=NUM_TASKS; i++)
    {
        /* Until we've used all threads in * 
         * the pool, do not need to wait * 
         * for one to exit              */
        if(i > THREAD_POOL_SIZE)
        {
            /* Wait for one thread to terminate */
            rc = WaitForMultipleObjects(
                THREAD_POOL_SIZE, 
                hThrds, 
                FALSE, 
                INFINITE); 

            slot = rc - WAIT_OBJECT_0; 
            MTVERIFY( slot >= 0 && 
                slot < THREAD_POOL_SIZE); 
            MTVERIFY(GetExitCodeThread(hThrds[slot], &exitCode)); 
            printf("thread #%d (slot %d) terminated\n", LOBYTE(exitCode), HIBYTE(exitCode)); 
            MTVERIFY(CloseHandle(hThrds[slot])); 
        }

        /* Cretae a new thread in the given 
         * available slot */
        MTVERIFY( hThrds[slot++] = CreateThread(NULL, 
            0, 
            ThreadFunc, 
            (LPVOID)MAKEWORD(i, slot+1), 
            0, 
            &threadId)); 

        printf("Launched thread #%d (slot %d)\n", i, slot); 
    }

    /* Now wait for all threads to terminate */
    rc = WaitForMultipleObjects(
        THREAD_POOL_SIZE, 
        hThrds, 
        TRUE, 
        INFINITE); 

    MTVERIFY(rc >= WAIT_OBJECT_0 && 
        rc < WAIT_OBJECT_0 + THREAD_POOL_SIZE); 

    for(slot = 0; slot < THREAD_POOL_SIZE; slot++)
    {
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
 * simulating some task that takes time. 
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
    printf("thread #%d (slot %d) wait for %d miliseconds\n", LOBYTE(n), HIBYTE(n), nWait); 
    return (DWORD)n; 
}
