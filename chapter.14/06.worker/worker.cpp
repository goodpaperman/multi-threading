// worker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/* 
 * Worker.cpp 
 * 
 * Sample code for "Multithreading Applications in Win32" 
 * This is from Chapter 14, Listing 14-3 
 * 
 * Demonstrate using worker threads that have 
 * their own message queue but no window.
 */

#define WIN32_LEAN_AND_MEAN 
#include <stdio.h> 
#include <stdlib.h>
#include <windows.h> 
#include <process.h> 
#include <string.h> 
#include "MtVerify.h" 

unsigned WINAPI ThreadFunc(void* p); 
HANDLE ghEvent; 

#define WM_JOB_PRINT_AS_IS      WM_APP + 0x0001
#define WM_JOB_PRINT_REVERSE    WM_APP + 0x0002
#define WM_JOB_PRINT_LOWER      WM_APP + 0x0003

int main(int argc, char* argv[])
{
    HANDLE hThread; 
    unsigned tid; 
    ghEvent = CreateEvent(NULL, TRUE, FALSE, NULL); 
    hThread = (HANDLE)_beginthreadex(NULL, 
        0, 
        ThreadFunc, 
        0, 
        0, 
        &tid); 

    MTVERIFY(hThread); 
    WaitForSingleObject(ghEvent, INFINITE); 

    char* szText = strdup("Thank you for buying this book.\n"); 
    PostThreadMessage(tid, WM_JOB_PRINT_AS_IS, NULL, (LPARAM)szText); 

    szText = strdup("Text is easier to read forward.\n"); 
    PostThreadMessage(tid, WM_JOB_PRINT_REVERSE, NULL, (LPARAM)szText); 

    szText = strdup("\nLOWER CASE IS FOR WHISPERING.\n"); 
    PostThreadMessage(tid, WM_JOB_PRINT_LOWER, NULL, (LPARAM)szText); 

    WaitForSingleObject(hThread, INFINITE); 
    CloseHandle(hThread); 
    CloseHandle(ghEvent); 
	return 0;
}

void CALLBACK TimerFunc(
                        HANDLE hwnd, 
                        UINT uMsg, 
                        UINT idEvent, 
                        DWORD dwTime)
{
    PostThreadMessage(GetCurrentThreadId(), WM_QUIT, 0, 0); 
}

unsigned WINAPI ThreadFunc(LPVOID n)
{
    MSG msg; 
    PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE); 
    SetEvent(ghEvent); 
    SetTimer(NULL, NULL, 2000, (TIMERPROC)TimerFunc); 

    while(GetMessage(&msg, NULL, 0, 0))
    {
        char* psz = (char*)msg.lParam; 
        switch(msg.message)
        {
        case WM_JOB_PRINT_AS_IS:
            printf("%s", psz); 
            free(psz); 
            break; 
        case WM_JOB_PRINT_REVERSE:
            printf("%s", strrev(psz)); 
            free(psz); 
            break; 
        case WM_JOB_PRINT_LOWER:
            printf("%s", _strlwr(psz)); 
            free(psz); 
            break; 
        default:
            DispatchMessage(&msg); 
        }
    }

    return 0; 
}
