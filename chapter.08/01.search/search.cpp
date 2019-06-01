// search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/* 
 * SrchCrt.c 
 * 
 * Sample code for "Multithreading Applications in Win32" 
 * This is from Chapter 8, Listing 8-1 
 * 
 * Uses multiple threads to search the files 
 * "*.c" in the current directory for the string 
 * given on the command line. 
 * 
 * This example uses the multithreaded version of 
 * the C run-time library so as to be able to use 
 * the FILE functions as well as calloc and free. 
 * 
 * Build this file with the command line: cl /MD SrchCrt.c 
 * 
 */

#define WIN32_LEAN_AND_MEAN 
#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 
#include <process.h> 
#include <stddef.h> 
#include "MtVerify.h" 

UINT WINAPI SearchProc( void* arg ); 
#define MAX_THREADS 3 
HANDLE hThreadLimitSemaphore; 
char szSearchFor[1024]; 

int main(int argc, char* argv[])
{
    WIN32_FIND_DATA *lpFindData; 
    HANDLE hFindFile; 
    HANDLE hThread; 
    UINT dummy; 
    int i; 

    if(argc != 2)
    {
        printf("Usage: %s <search-string>\n", argv[0]); 
        return EXIT_FAILURE; 
    }

    strcpy(szSearchFor, argv[1]); 
    lpFindData = (WIN32_FIND_DATA*)calloc(1, sizeof(WIN32_FIND_DATA));
    hFindFile = FindFirstFile("*.cpp", lpFindData); 
    if(hFindFile == INVALID_HANDLE_VALUE)
    {
        int error = GetLastError(); 
        printf("Error = %d\n", error); 
        free(lpFindData); 
        return EXIT_FAILURE; 
    }

    MTVERIFY( hThreadLimitSemaphore = CreateSemaphore(
        NULL, 
        MAX_THREADS, 
        MAX_THREADS, 
        NULL ) 
        ); 

    do
    {
        WaitForSingleObject(hThreadLimitSemaphore, INFINITE); 
        MTVERIFY( 
            hThread = (HANDLE)_beginthreadex(NULL, 
            0, 
            SearchProc, 
            lpFindData, 
            0, 
            &dummy)
            ); 

        MTVERIFY(CloseHandle(hThread)); 
        lpFindData = (WIN32_FIND_DATA*)calloc(1, sizeof(WIN32_FIND_DATA));
    }while(FindNextFile(hFindFile, lpFindData)); 

    FindClose(hFindFile); 
    for(i=0; i<MAX_THREADS; i++)
    {
        WaitForSingleObject(hThreadLimitSemaphore, 
            INFINITE); 
    }

    MTVERIFY( CloseHandle(hThreadLimitSemaphore) ); 
	return EXIT_SUCCESS;
}

UINT _stdcall SearchProc(void *arg)
{
    WIN32_FIND_DATA *lpFindData = (WIN32_FIND_DATA*) arg; 
    char buf[1024]; 
    FILE* fp; 

    fp = fopen(lpFindData->cFileName, "r"); 
    if(!fp)
    {
        free(lpFindData); 
        ReleaseSemaphore(hThreadLimitSemaphore, 1, NULL); 
        return EXIT_FAILURE; 
    }

    while(fgets(buf, sizeof(buf), fp))
    {
        if(strstr(buf, szSearchFor))
            printf("%s: %s", lpFindData->cFileName, buf); 
    }

    fclose(fp); 
    free(lpFindData); 
    
    MTVERIFY( ReleaseSemaphore( hThreadLimitSemaphore, 1, NULL ) ); 
    return EXIT_SUCCESS; 
}
