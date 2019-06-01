// badclass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/*
 * BadClass.cpp 
 * 
 * Sample code for "Multithreading Applications in Win32" 
 * This is from Chapter 9, Listing 9-2 
 * 
 * Shows the wrong way to try and start a thread 
 * based on a class member function. 
 * 
 * THIS FILE IS NOT SUPPOSED TO COMPILE SUCCESSFULLY 
 * You should get an error on line 51. 
 * 
 * Build this file with the command line: 
 * 
 *   cl /MD BadClass.cpp 
 * 
 */

#define WIN32_MEAN_AND_LEAN
#include <windows.h> 
#include <stdio.h> 
#include <process.h> 

typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC) (
                                                      LPVOID lpThreadParameter
                                                      ); 
typedef unsigned *PBEGINTHREADEX_THREADID; 

class ThreadObject
{
public: 
    ThreadObject(); 
    void StartThread(); 
    virtual DWORD WINAPI ThreadFunc(LPVOID param); 
    //virtual unsigned WINAPI ThreadFunc(LPVOID param); 
    void WaitForExit(); 
private:
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
        //ThreadFunc, 
        0, 
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

//unsigned WINAPI ThreadObject::ThreadFunc(LPVOID param)
DWORD WINAPI ThreadObject::ThreadFunc(LPVOID param) 
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