// string.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#define WIN32_MEAN_AND_LEAN
//#include <windows.h> 
#include <stdio.h> 
#include <afxmt.h> 

class StringV3 
{
public:
    StringV3(); 
    virtual ~StringV3();
    virtual void Set(char* str); 
    int GetLength(); 
    void Truncate(int length); 

private:
    CCriticalSection m_Sync; 
public:
    char* m_pData; 
}; 

StringV3::StringV3()
{
    // The constructor for m_Sync will have 
    // already been called automatically because 
    // it is a member variable. 
    m_pData = NULL; 
}

StringV3::~StringV3()
{
    // Use the "array delete" operator 
    // Note: "delete" checks for NULL automatically 
    m_Sync.Lock(); 
    delete[] m_pData; 
    m_Sync.Unlock(); 
    // The destructor for m_Sync will be 
    // called automatically. 
}

void StringV3::Set(char* str)
{
    m_Sync.Lock(); 
    delete[] m_pData; 
    m_pData = new char[::strlen(str)+1]; 
    ::strcpy(m_pData, str);
    m_Sync.Unlock();
}

int StringV3::GetLength()
{
    if(m_pData == NULL)
        return 0; 

    m_Sync.Lock(); 
    int len = ::strlen(m_pData); 
    m_Sync.Unlock(); 
    return len; 
}

void StringV3::Truncate(int length)
{
    if(m_pData == NULL)
        return; 

    m_Sync.Lock(); 
    if(length >= GetLength())
    {
        m_Sync.Unlock(); 
        return; 
    }

    m_pData[length] = '\0'; 
    m_Sync.Unlock(); 
}


class StringV4 
{
public:
    StringV4(); 
    virtual ~StringV4();
    virtual void Set(char* str); 
    int GetLength(); 
    void Truncate(int length); 

private:
    CSyncObject* m_pLockable; 
public:
    char* m_pData; 
}; 

StringV4::StringV4()
{
    m_pLockable = new CMutex; 
    m_pData = NULL; 
}

StringV4::~StringV4()
{
    delete m_pLockable; 
    delete[] m_pData; 
}

void StringV4::Set(char* str)
{
    CSingleLock localLock(m_pLockable, TRUE); 
    delete[] m_pData; // In case new throws an exception 
    m_pData = new char[::strlen(str)+1]; 
    ::strcpy(m_pData, str);
}

int StringV4::GetLength()
{
    CSingleLock localLock(m_pLockable, TRUE); 
    if(m_pData == NULL)
        return 0; 

    return ::strlen(m_pData); 
}

void StringV4::Truncate(int length)
{
    CSingleLock localLock(m_pLockable); 
    if(m_pData == NULL)
        return; 

    if(length >= GetLength())
        return; 

    m_pData[length] = '\0'; 
}


int main(int argc, char* argv[])
{
    StringV4 str; 
    str.Set("Multithreading"); 
    printf("%s\n", str.m_pData); 
    str.Truncate(5); 
    printf("%s\n", str.m_pData); 
    str.Truncate(15); 
    printf("%s\n", str.m_pData); 
    str.Set(""); 
    printf("%s\n", str.m_pData); 
    //str.Set(NULL); 
    StringV4 str2; 
    printf("%s\n", str2.m_pData); 
	return 0;
}
