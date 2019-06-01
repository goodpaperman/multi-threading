// list.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h> 
#include <stdlib.h> 
#include <stdio.h> 

typedef struct _Node 
{
    struct _Node *next; 
    int data; 
} Node; 

typedef struct _List 
{
    Node* head; 
    //CRITICAL_SECTION critical_sec; 
    HANDLE hMutex; 
} List; 

List *CreateList()
{
    List* pList = (List *)malloc(sizeof(List)); 
    pList->head = NULL; 
    //InitializeCriticalSection(&pList->critical_sec); 
    pList->hMutex = CreateMutex(NULL, FALSE, NULL); 
    return pList; 
}

void DeleteList(List* pList)
{
    //DeleteCriticalSection(&pList->critical_sec); 
    CloseHandle(pList->hMutex); 
    free(pList); 
}

void AddHead(List* pList, Node* node)
{
    //EnterCriticalSection(&pList->critical_sec); 
    WaitForSingleObject(pList->hMutex, INFINITE); 
    node->next = pList->head; 
    pList->head = node; 
    ReleaseMutex(pList->hMutex); 
    //LeaveCriticalSection(&pList->critical_sec); 
}

void Insert(List* pList, Node* afterNode, Node* newNode)
{
    //EnterCriticalSection(&pList->critical_sec); 
    WaitForSingleObject(pList->hMutex, INFINITE); 
    if(afterNode == NULL)
    {
        AddHead(pList, newNode); 
    }
    else 
    {
        newNode->next = afterNode->next; 
        afterNode->next = newNode; 
    }
    ReleaseMutex(pList->hMutex); 
    //LeaveCriticalSection(&pList->critical_sec); 
}

Node* Next(List* pList, Node* node)
{
    Node* next; 
    //EnterCriticalSection(&pList->critical_sec); 
    WaitForSingleObject(pList->hMutex, INFINITE); 
    next = node->next; 
    ReleaseMutex(pList->hMutex); 
    //LeaveCriticalSection(&pList->critical_sec); 
    return next; 
}

void SwapLists(List* list1, List* list2, int nThread)
{
    //Node* tmp; 
    //EnterCriticalSection(&list1->critical_sec); 
    //printf("Thread #%d: Enter list%d critical section, want list%d critical section\n", 
    //    nThread, list1->head->data, list2->head->data); 
    //EnterCriticalSection(&list2->critical_sec); 
    //printf("Thread #%d: Enter list%d critical section\n", nThread, list2->head->data);
    //tmp = list1->head; 
    //list1->head = list2->head; 
    //list2->head = tmp; 
    //LeaveCriticalSection(&list1->critical_sec); 
    //LeaveCriticalSection(&list2->critical_sec); 
    //printf("Thread #%d: Swap completed.\n", nThread); 

    Node* tmp; 
    HANDLE arrhandles[2]; 
    arrhandles[0] = list1->hMutex; 
    arrhandles[1] = list2->hMutex;     
    printf("Thread #%d: wait mutex for list%d and list%d\n", 
        nThread, list1->head->data, list2->head->data); 
    WaitForMultipleObjects(2, arrhandles, TRUE, INFINITE); 
    tmp = list1->head; 
    list1->head = list2->head; 
    list2->head = tmp; 
    ReleaseMutex(arrhandles[0]); 
    ReleaseMutex(arrhandles[1]); 
    printf("Thread #%d: Swap completed.\n", nThread); 
}

List* list1 = CreateList(); 
List* list2 = CreateList(); 
DWORD WINAPI SwapListProc(LPVOID pParam)
{
    int i = 0; 
    while(i++ < 10000)
    {
        //printf("Swap list%d with list%d in thread %d\n", list1->head->data, list2->head->data, (int)pParam); 
        SwapLists(list1, list2, (int)pParam); 
        //printf("Swap list%d with list%d in thread %d\n", list2->head->data, list1->head->data, (int)pParam); 
        SwapLists(list2, list1, (int)pParam); 
    }

    return i; 
}

int main(int argc, char* argv[])
{    
    Node* node1 = (Node*)malloc(sizeof(Node)); 
    node1->data = 1; 
    AddHead(list1, node1);

    Node* node2 = (Node*)malloc(sizeof(Node)); 
    node2->data = 2; 
    AddHead(list2, node2); 
    //Insert(list2, NULL, node2);  

    HANDLE hThread[2]; 
    hThread[0] = CreateThread(
        NULL, 
        0, 
        SwapListProc, 
        (LPVOID)1, 
        0, 
        NULL); 

    hThread[1] = CreateThread(
        NULL, 
        0, 
        SwapListProc, 
        (LPVOID)2, 
        0, 
        NULL); 

    ::WaitForMultipleObjects(
        2, 
        hThread, 
        TRUE, 
        INFINITE); 

    CloseHandle(hThread[0]); 
    CloseHandle(hThread[1]); 

    free(list1->head); 
    free(list2->head); 

    DeleteList(list1); 
    DeleteList(list2); 
	return 0;
}
