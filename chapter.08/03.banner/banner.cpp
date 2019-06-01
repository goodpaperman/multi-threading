// banner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/* 
 * Banner.c 
 * 
 * Sample code for "Multithreading Applications in Win32" 
 * This is from Chapter 8, Listing 8-3
 * 
 * Demonstrates how to write a program that can use 
 * CreateThread instead of calling _beginthreadex. 
 * This program does not need the multithread library. 
 * 
 * This program could use ReadConsole and WriteConsole. 
 * There are minor but significant differences between 
 * these functions and ReadFile and WriteFile. 
 * 
 * This program is ANSI only, it will not compile 
 * for Unicode. 
 */ 

#define WIN32_LEAN_AND_MEAN 
#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 
#include <time.h> 
#include "mtverify.h" 

#define MAX_THREADS 64
#define INPUT_BUF_SIZE 80 
#define BANNER_SIZE 12 
#define OUTPUT_TEXT_COLOR BACKGROUND_BLUE | \
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE 

void MainLoop(); 
void ClearScreen(); 
void ShutDownThreads(); 
void Prompt(LPCSTR str); 
int StripCr(LPSTR buf); 

DWORD WINAPI BannerProc(LPVOID pParam); 

HANDLE hConsoleIn; 
HANDLE hConsoleOut; 
HANDLE hRunObject; 
HANDLE ThreadHandles[MAX_THREADS]; 
int nThreads; 

CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 

typedef struct 
{
    TCHAR buf[INPUT_BUF_SIZE]; 
    SHORT x; 
    SHORT y; 
}DataBlock; 

int main(int argc, char* argv[])
{
    hConsoleIn = GetStdHandle( STD_INPUT_HANDLE ); 
    hConsoleOut = GetStdHandle( STD_OUTPUT_HANDLE ); 
    GetConsoleScreenBufferInfo( hConsoleOut, &csbiInfo); 

    ClearScreen(); 

    MTVERIFY( hRunObject = CreateEvent(
        NULL, 
        TRUE, 
        0, 
        NULL)
        ); 

    MainLoop(); 
    ShutDownThreads(); 
    ClearScreen(); 

    CloseHandle( hRunObject ); 
    CloseHandle( hConsoleIn ); 
    CloseHandle( hConsoleOut ); 
	return EXIT_SUCCESS;
}

void ClearScreen()
{
    DWORD dummy; 
    COORD Home = { 0, 0 }; 
    FillConsoleOutputAttribute( hConsoleOut, 
        csbiInfo.wAttributes, 
        csbiInfo.dwSize.X * csbiInfo.dwSize.Y, 
        Home, 
        &dummy ); 

    FillConsoleOutputCharacter( hConsoleOut, 
        ' ', 
        csbiInfo.dwSize.X * csbiInfo.dwSize.Y, 
        Home, 
        &dummy ); 
}

void MainLoop()
{
    TCHAR buf[INPUT_BUF_SIZE]; 
    DWORD bytesRead; 
    DataBlock* data_block; 
    DWORD thread_id; 
    srand(time(NULL)); 

    for(;;)
    {
        Prompt(
            "Type string to display or ENTER to exit: "
            ); 

        MTVERIFY( ReadFile( hConsoleIn, 
            buf, 
            INPUT_BUF_SIZE - 1, 
            &bytesRead, 
            NULL)
            ); 

        buf[bytesRead] = 0; 
        MTVERIFY( FlushConsoleInputBuffer( hConsoleIn ) ); 
        if(StripCr( buf ) == 0)
            break; 

        if(nThreads < MAX_THREADS)
        {
            data_block = (DataBlock*)HeapAlloc(
                GetProcessHeap(), 
                HEAP_ZERO_MEMORY, 
                sizeof(DataBlock)); 
            strcpy(data_block->buf, buf); 
            data_block->x = rand()
                * (csbiInfo.dwSize.X - BANNER_SIZE) 
                / RAND_MAX; 
            data_block->y = rand() 
                * (csbiInfo.dwSize.Y - 1) 
                / RAND_MAX + 1; 

            MTVERIFY(
                ThreadHandles[nThreads++] = CreateThread(
                NULL, 
                0, 
                BannerProc, 
                data_block, 
                0, 
                &thread_id) ); 
        }
    }
}

void Prompt(LPCSTR str)
{
    COORD Home = { 0, 0 }; 
    DWORD dummy; 
    int len = strlen(str); 
    SetConsoleCursorPosition( hConsoleOut, Home ); 
    WriteFile( hConsoleOut, str, len, &dummy, NULL ); 
    Home.X = len; 
    FillConsoleOutputCharacter( hConsoleOut, 
        ' ', 
        csbiInfo.dwSize.X - len, 
        Home, 
        &dummy ); 
}

int StripCr( LPSTR buf )
{
    int len = strlen(buf); 
    for(;;)
    {
        if (len <= 0) return 0; 
        else if( buf[--len] == '\r' )
            buf[len] = ' '; 
        else if( buf[len] == '\n' )
            buf[len] = ' '; 
        else break; 
    }

    return len; 
}

void ShutDownThreads()
{
    if(nThreads > 0)
    {
        MTVERIFY( SetEvent( hRunObject ) ); 
        MTVERIFY( WaitForMultipleObjects( 
            nThreads, 
            ThreadHandles, 
            TRUE, 
            INFINITE) != WAIT_FAILED ); 

        while(--nThreads)
            MTVERIFY( CloseHandle( 
            ThreadHandles[nThreads] ) ); 
    }
}

DWORD WINAPI BannerProc( LPVOID pParam )
{
    DataBlock* thread_data_block = (DataBlock*)pParam; 
    COORD TopLeft = { 0, 0 }; 
    COORD Size = { BANNER_SIZE, 1 }; 
    int i, j; 
    int len; 
    int ScrollPosition = 0; 
    TCHAR OutputBuf[INPUT_BUF_SIZE + BANNER_SIZE]; 
    CHAR_INFO CharBuf[INPUT_BUF_SIZE + BANNER_SIZE]; 
    SMALL_RECT rect; 

    rect.Left = thread_data_block->x; 
    rect.Right = rect.Left + BANNER_SIZE; 
    rect.Top = thread_data_block->y; 
    rect.Bottom = rect.Top; 

    strcpy(OutputBuf, thread_data_block->buf); 
    len = strlen(OutputBuf); 
    for(i=len; i<BANNER_SIZE; i++)
        OutputBuf[i] = ' '; 

    if(len < BANNER_SIZE) len = BANNER_SIZE; 
    strncpy(OutputBuf+len, OutputBuf, BANNER_SIZE); 
    OutputBuf[len+BANNER_SIZE-1] = '\0'; 

    MTVERIFY( HeapFree( GetProcessHeap(), 0, pParam ) ); 

    do 
    {
        for(i=ScrollPosition++, j=0; 
        j<BANNER_SIZE; i++, j++)
        {
            CharBuf[j].Char.AsciiChar = OutputBuf[i]; 
            CharBuf[j].Attributes = OUTPUT_TEXT_COLOR; 
        }

        if(ScrollPosition == len)
            ScrollPosition = 0; 

        MTVERIFY( WriteConsoleOutput( 
            hConsoleOut, 
            CharBuf, 
            Size, 
            TopLeft, 
            &rect) ); 
    }while( WaitForSingleObject( hRunObject, 125L ) == WAIT_TIMEOUT ); 

    return 0; 
}