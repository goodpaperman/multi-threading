// criticalsection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define WIN32_MEAN_AND_LEAN
#include <windows.h> 
#include <stdio.h> 

class CriticalSection
{
public:
    CriticalSection(); 
    ~CriticalSection(); 
    void Enter(); 
    void Leave(); 
private:
    CRITICAL_SECTION m_CritSect; 
}; 

CriticalSection::CriticalSection()
{
    InitializeCriticalSection(&m_CritSect); 
}

CriticalSection::~CriticalSection()
{
    DeleteCriticalSection(&m_CritSect); 
}

void CriticalSection::Enter()
{
    EnterCriticalSection(&m_CritSect); 
}

void CriticalSection::Leave()
{
    LeaveCriticalSection(&m_CritSect);
}

class Lock
{
public:
    Lock(CriticalSection* pCritSet); 
    ~Lock(); 

private:
    CriticalSection* m_pCritical; 
}; 

Lock::Lock(CriticalSection* pCritSect)
{
    m_pCritical = pCritSect; 
    m_pCritical->Enter(); 
}

Lock::~Lock()
{
    m_pCritical->Leave(); 
}

class String 
{
public:
    String(); 
    virtual ~String();
    virtual void Set(char* str); 
    int GetLength(); 
    void Truncate(int length); 

private:
    CriticalSection m_Sync; 
public:
    char* m_pData; 
}; 

String::String()
{
    // The constructor for m_Sync will have 
    // already been called automatically because 
    // it is a member variable. 
    m_pData = NULL; 
}

String::~String()
{
    // Use the "array delete" operator 
    // Note: "delete" checks for NULL automatically 
    m_Sync.Enter();
    delete[] m_pData; 
    m_Sync.Leave(); 
    // The destructor for m_Sync will be 
    // called automatically. 
}

void String::Set(char* str)
{
    m_Sync.Enter(); 
    delete[] m_pData; 
    m_pData = new char[::strlen(str)+1]; 
    ::strcpy(m_pData, str);
    m_Sync.Leave();
}

int String::GetLength()
{
    if(m_pData == NULL)
        return 0; 

    m_Sync.Enter(); 
    int len = ::strlen(m_pData); 
    m_Sync.Leave(); 
    return len; 
}

void String::Truncate(int length)
{
    if(m_pData == NULL)
        return; 

    //m_Sync.Enter(); 
    //if(length >= GetLength())
    //{
    //    m_Sync.Leave(); 
    //    return; 
    //}

    //m_pData[length] = '\0'; 
    //m_Sync.Leave(); 

    // Declaring a "Lock" variable will call 
    // the constructor automatically. 
    Lock lock(&m_Sync); 
    if(length >= GetLength())
        return; 

    m_pData[length] = '\0'; 
    // lock cleans itself up automatically 
}


class LockableObject 
{
public:
    LockableObject() {} 
    virtual ~LockableObject() {} 
    virtual void Lock() = 0; 
    virtual void Unlock() = 0; 
}; 

class CriticalSectionV2 : public LockableObject 
{
public:
    CriticalSectionV2(); 
    virtual ~CriticalSectionV2(); 
    virtual void Lock(); 
    virtual void Unlock(); 

private: 
    CRITICAL_SECTION m_CritSect; 
}; 

CriticalSectionV2::CriticalSectionV2()
{
    InitializeCriticalSection(&m_CritSect); 
}

CriticalSectionV2::~CriticalSectionV2()
{
    DeleteCriticalSection(&m_CritSect); 
}

void CriticalSectionV2::Lock()
{
    EnterCriticalSection(&m_CritSect); 
}

void CriticalSectionV2::Unlock()
{
    LeaveCriticalSection(&m_CritSect);
}

class LockV2
{
public:
    LockV2(LockableObject* pLockable); 
    ~LockV2(); 

private:
    LockableObject* m_pLockable; 
}; 

LockV2::LockV2(LockableObject* pLockable)
{
    m_pLockable = pLockable; 
    m_pLockable->Lock(); 
}

LockV2::~LockV2()
{
    m_pLockable->Unlock(); 
}

class StringV2 
{
public:
    StringV2(); 
    virtual ~StringV2();
    virtual void Set(char* str); 
    int GetLength(); 
    void Truncate(int length); 

private:
    CriticalSectionV2 m_Lockable; 
public:
    char* m_pData; 
}; 

StringV2::StringV2()
{
    m_pData = NULL; 
}

StringV2::~StringV2()
{
    // The program must ensure that 
    // it is safe to destroy the object. 
    delete[] m_pData; 
}

void StringV2::Set(char* str)
{
    LockV2 localLock(&m_Lockable); 
    delete[] m_pData; 
    m_pData = new char[::strlen(str)+1]; 
    ::strcpy(m_pData, str);
}

int StringV2::GetLength()
{
    LockV2 localLock(&m_Lockable); 
    if(m_pData == NULL)
        return 0; 

    return ::strlen(m_pData); 
}

void StringV2::Truncate(int length)
{
    LockV2 lock(&m_Lockable); 
    if(m_pData == NULL)
        return; 

    if(length >= GetLength())
        return; 

    m_pData[length] = '\0'; 
}


int main(int argc, char* argv[])
{
    StringV2 str; 
    str.Set("Multithreading"); 
    printf("%s\n", str.m_pData); 
    str.Truncate(5); 
    printf("%s\n", str.m_pData); 
    str.Truncate(15); 
    printf("%s\n", str.m_pData); 
    str.Set(""); 
    printf("%s\n", str.m_pData); 
    //str.Set(NULL); 
    StringV2 str2; 
    printf("%s\n", str2.m_pData); 
	return 0;
}
