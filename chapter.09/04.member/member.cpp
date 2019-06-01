// member.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/*
 * Member.cpp 
 * 
 * Sample code for "Multithreading Applications in Win32" 
 * This is from Chapter 9, Listing 9-3 
 * 
 * Shows how to start a thread based on a 
 * class member function using a static 
 * member function. 
 * 
 * Build this file with the command line: 
 * 
 *   cl /MD Member.cpp 
 * 
 */

#define WIN32_MEAN_AND_LEAN
#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 
#include <process.h> 

typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC) (
                                                      LPVOID lpThreadParameter
                                                      ); 
typedef unsigned *PBEGINTHREADEX_THREADID; 

DWORD WINAPI ThreadFunc(LPVOID param); 

class ThreadObject
{
public: 
    ThreadObject(); 
    void StartThread(); 
    void WaitForExit(); 

    // Thread member function must be public
    // or the C-style function will not have 
    // access rights. 
    virtual DWORD ThreadMemberFunc(); 

protected:   
    HANDLE m_hThread; 
    DWORD m_ThreadId; 
}; 

ThreadObject::ThreadObject()
{
    m_hThread = NULL; 
    m_ThreadId = 0; 
}

void ThreadObject::StartThread()
{
    m_hThread = (HANDLE)_beginthreadex(NULL, 
        0, 
        (PBEGINTHREADEX_THREADFUNC)ThreadFunc, 
        (LPVOID)this, 
        0, 
        (PBEGINTHREADEX_THREADID)&m_ThreadId ); 

    if(m_hThread)
        printf("Thread launched\n"); 
}

void ThreadObject::WaitForExit()
{
    WaitForSingleObject(m_hThread, INFINITE); 
    CloseHandle(m_hThread); 
}

DWORD WINAPI ThreadFunc(LPVOID param) 
{
    ThreadObject* pto = (ThreadObject*)param; 
    return pto->ThreadMemberFunc(); 
}

DWORD ThreadObject::ThreadMemberFunc()
{
    return 0; 
}

int main(int argc, char* argv[])
{
    ThreadObject obj; 
    obj.StartThread(); 
    obj.WaitForExit(); 
    return EXIT_SUCCESS; 
}