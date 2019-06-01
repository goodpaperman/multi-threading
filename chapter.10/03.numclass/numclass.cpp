// numclass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/* 
 * NumClass.cpp 
 * 
 * Sample code for "Multithreading Applications in Win32" 
 * This is from Chapter 10, Listing 10-3 
 * 
 * Demonstrate worker thread startup in MFC 
 * without AfxBeginThread. 
 * 
 * Compile with the IDE or: nmake -f NumClass.mak 
 */ 

#include <afxwin.h> 
CWinApp TheApp; 

class CUserThread : public CWinThread 
{
public:
    CUserThread(AFX_THREADPROC pfnThreadProc); 
    static UINT ThreadFunc(LPVOID param); 

public:
    int m_nStartCounter; 

private:
    virtual void Go(); 
}; 

CUserThread::CUserThread(AFX_THREADPROC pfnThreadProc) 
: CWinThread(pfnThreadProc, NULL) //this) 
{
    m_bAutoDelete = FALSE; 
    m_pThreadParams = this; 
}

UINT CUserThread::ThreadFunc(LPVOID param)
{
    CUserThread* pThread = (CUserThread*)param; 
    pThread->Go(); 
    return 0; 
}

void CUserThread::Go()
{
    int n = m_nStartCounter; 
    for(int i=0; i<10; i++)
        printf("%d%d%d%d%d%d%d%d\n", n, n, n, n, n, n, n, n); 
}

int main()
{
    CUserThread* pThreads[5]; 
    for(int i=0; i<5; i++)
    {
        pThreads[i] = new CUserThread( CUserThread::ThreadFunc ); 
        pThreads[i]->m_nStartCounter = i; 
        VERIFY( pThreads[i]->CreateThread() ); 
        printf("Thread launched %d\n", i); 
    }

    for(i=0; i<5; i++)
    {
        WaitForSingleObject(pThreads[i]->m_hThread, INFINITE); 
        delete pThreads[i]; 
    }

    return 0; 
}
