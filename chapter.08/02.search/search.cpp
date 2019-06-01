// search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/* 
 * SrchWin.c
 * 
 * Sample code for "Multithreading Application in Win32" 
 * This is from Chapter 8, Listing 8-2 
 * 
 * Uses multiple threads to search the files 
 * "*.c" in the current directory for the string 
 * given on the command line 
 * 
 * This example avoids most C run-time functions 
 * so that it can use the single-threaded 
 * C libraries.
 * 
 * It is necessary to use a critical section to 
 * divvy up output to the screen or the various
 * threads end up with their output intermingled.
 * Normally the multithreaded C run-time does this 
 * automatically if you use printf.
 * 
 */ 

#include <windows.h> 
#include "MtVerify.h" 

DWORD WINAPI SearchProc( void* arg ); 
BOOL GetLine( HANDLE hFile, LPSTR buf, DWORD size ); 

#define MAX_THREADS 3 

HANDLE hThreadLimitSemaphore; 
HANDLE hConsoleOut; 
CRITICAL_SECTION ScreenCritical; 

char szSearchFor[1024]; 

int main(int argc, char* argv[])
{
    WIN32_FIND_DATA *lpFindData; 
    HANDLE hFindFile; 
    HANDLE hThread; 
    DWORD dummy; 
    int i; 

    hConsoleOut = GetStdHandle( STD_OUTPUT_HANDLE ); 
    if(argc != 2)
    {
        char errbuf[512]; 
        wsprintf(errbuf, 
            "Usage: %s <search-string>\n", 
            argv[0]); 
        WriteFile( hConsoleOut, 
            errbuf, 
            strlen(errbuf), 
            &dummy, 
            FALSE ); 

        return EXIT_FAILURE; 
    }

    strcpy(szSearchFor, argv[1]); 
    lpFindData = (WIN32_FIND_DATA *)HeapAlloc( GetProcessHeap(), 
        HEAP_ZERO_MEMORY, 
        sizeof(WIN32_FIND_DATA) ); 
    hFindFile = FindFirstFile( "*.cpp", lpFindData ); 
    if(hFindFile == INVALID_HANDLE_VALUE)
    {
        HeapFree( GetProcessHeap(), 
            0, 
            lpFindData ); 
        return EXIT_FAILURE; 
    }

    MTVERIFY( hThreadLimitSemaphore = CreateSemaphore(
        NULL, 
        MAX_THREADS, 
        MAX_THREADS, 
        NULL ) ); 

    InitializeCriticalSection(&ScreenCritical); 

    do
    {
        WaitForSingleObject( hThreadLimitSemaphore, INFINITE ); 
        MTVERIFY( hThread = CreateThread(
            NULL, 
            0, 
            SearchProc, 
            lpFindData, 
            0, 
            &dummy) ); 

        MTVERIFY( CloseHandle( hThread ) ); 
        lpFindData = (WIN32_FIND_DATA *)HeapAlloc( GetProcessHeap(), 
            HEAP_ZERO_MEMORY, 
            sizeof(WIN32_FIND_DATA)); 
    }while( FindNextFile( hFindFile, lpFindData )); 

    FindClose(hFindFile); 
    for(i=0; i<MAX_THREADS; i++)
        WaitForSingleObject( hThreadLimitSemaphore, INFINITE ); 

    DeleteCriticalSection(&ScreenCritical); 
    MTVERIFY( CloseHandle(hThreadLimitSemaphore) ); 
	return EXIT_SUCCESS;
}

DWORD WINAPI SearchProc( void *arg )
{
    WIN32_FIND_DATA *lpFindData = (WIN32_FIND_DATA *)arg; 
    char buf[1024]; 
    char line[2048]; 
    HANDLE hFile; 
    DWORD dummy; 

    hFile = CreateFile(lpFindData->cFileName, 
        GENERIC_READ, 
        FILE_SHARE_READ, 
        NULL, 
        OPEN_EXISTING, 
        FILE_FLAG_SEQUENTIAL_SCAN, 
        NULL ); 

    if(!hFile)
    {
        HeapFree( GetProcessHeap(), 0, lpFindData ); 
        MTVERIFY( ReleaseSemaphore( hThreadLimitSemaphore, 1, NULL ) ); 
        return EXIT_FAILURE; 
    }

    while(GetLine( hFile, buf, sizeof(buf) ))
    {
        if(strstr(buf, szSearchFor))
        {
            EnterCriticalSection(&ScreenCritical); 
            wsprintf(line, "%s: %s\r\n", lpFindData->cFileName, buf); 
            WriteFile( hConsoleOut, line, strlen(line), &dummy, NULL ); 
            LeaveCriticalSection(&ScreenCritical); 
        }
    }

    CloseHandle(hFile); 
    HeapFree( GetProcessHeap(), 0, lpFindData ); 
    MTVERIFY( ReleaseSemaphore( hThreadLimitSemaphore, 1, NULL ) ); 
    return EXIT_SUCCESS; 
}

BOOL GetLine(HANDLE hFile, LPSTR buf, DWORD size)
{
    DWORD total = 0; 
    DWORD numread; 
    int state = 0; 

    for(;;)
    {
        if(total == size-1)
        {
            buf[size-1] = '\0'; 
            return TRUE; 
        }

        if(!ReadFile(hFile, buf+total, 1, &numread, 0) || numread == 0)
        {
            buf[total] = '\0'; 
            return total != 0; 
        }

        if(buf[total] == '\t' || buf[total] == '\n')
        {
            if(state == 0)
                continue; 

            buf[total] = '\0'; 
            return TRUE; 
        }

        state = 1; 
        total ++; 
    }
}