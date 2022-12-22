#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <cstdio>
#include <condition_variable>
#include "Array.h"

constexpr int WaitForEndTime = 200;
constexpr int MaxSynchoTime = 500;
constexpr int SleepTime = 5;

Array information;

CRITICAL_SECTION struct_work;
HANDLE* MarkerN_wait;
HANDLE* MarkerN_console_resume;
HANDLE* MarkerN_console_stop;

DWORD WINAPI Marker(LPVOID number)
{
    EnterCriticalSection(&struct_work); 

    int num = *(int*)(number);
    int index;
    int marked_count;
    int* marked_array = new int[information.size];

    for (size_t i = 0; i < information.size; i++)
    {
        marked_array[i] = 0;
    }

    srand(num);
    marked_count = 0;
    while (true)
    {
        index = rand() % information.size;

        if (information.Arr[index] == 0)
        {
            Sleep(SleepTime);
            information.Arr[index] = num;
            marked_count++; 
            marked_array[index] = 1; 
            Sleep(SleepTime);
        }
        else
        {
            printf("Thread number: %d, marked_count: %d, unmarked index: %d \n", num, marked_count, index);
            SetEvent(MarkerN_wait[num - 1]);  
            LeaveCriticalSection(&struct_work); 

            WaitForSingleObject(MarkerN_console_stop[num - 1], INFINITE);

            if (WAIT_OBJECT_0 == WaitForSingleObject(MarkerN_console_resume[num - 1], WaitForEndTime))
            {
                EnterCriticalSection(&struct_work);
            }
            else
            {
                EnterCriticalSection(&struct_work); 
                break;
            }
        }
    }

    for (size_t i = 0; i < information.size; i++)
    {
        if (marked_array[i] == 1)
        {
            information.Arr[i] = 0;
        }
    }

    LeaveCriticalSection(&struct_work);

    ExitThread(0);
}

int main() {
    int synchronization_time = 0;
    int thread_emount = 0;
    printf("Enter array size: ");
    scanf_s("%d", &information.size);
    printf("Enter marker thread emount: ");
    scanf_s("%d", &thread_emount);

    if (thread_emount != 0)
    {
        synchronization_time = MaxSynchoTime / thread_emount;
    }

    information.Arr = new int[information.size];
    for (int i = 0; i < information.size; ++i)
    {
        information.Arr[i] = 0;
    }

    HANDLE* hThread = new HANDLE[thread_emount];

    MarkerN_wait = new HANDLE[thread_emount];
    MarkerN_console_resume = new HANDLE[thread_emount];
    MarkerN_console_stop = new HANDLE[thread_emount];

    for (int i = 0; i < thread_emount; i++)
    {
        MarkerN_wait[i] = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        MarkerN_console_resume[i] = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        MarkerN_console_stop[i] = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    }

    InitializeCriticalSection(&struct_work);

    int* end_of_threads = new int[thread_emount];
    for (int i = 0; i < thread_emount; ++i)
    {
        end_of_threads[i] = 1; 
    }

    int* numbers = new int[thread_emount]; 

    for (int i = 0; i < thread_emount; i++)
    {
        numbers[i] = i + 1;
        hThread[i] = CreateThread(nullptr, 0, Marker, &numbers[i], CREATE_SUSPENDED, nullptr);
        ResumeThread(hThread[i]);

        Sleep(synchronization_time);
    }

    while (!allZero(end_of_threads, thread_emount)) 
    {
        for (int i = 0; i < thread_emount; i++)
        {
            if (end_of_threads[i] != 0)
                WaitForSingleObject(MarkerN_wait[i], INFINITE);
        }

        int break_num;
        printf("Enter num of Marker() to break: ");
        do
        {
            scanf_s("%d", &break_num);
            if (end_of_threads[break_num - 1] == 0)
            {
                printf("This one is stopped, try another: ");
            }
        } while (end_of_threads[break_num - 1] == 0);
        break_num--;  

        SetEvent(MarkerN_console_stop[break_num]);
        WaitForSingleObject(hThread[break_num], INFINITE);

        printf("Array: ");
        for (int i = 0; i < information.size; ++i)
        {
            printf("%d ", information.Arr[i]);
        }
        printf("\n");

        end_of_threads[break_num] = 0; 

        for (size_t i = 0; i < thread_emount; i++)
        {
            if (end_of_threads[i] != 0)
            {
                SetEvent(MarkerN_console_stop[i]);
                SetEvent(MarkerN_console_resume[i]);

                Sleep(synchronization_time);
            }
        }

        CloseHandle(hThread[break_num]);
        CloseHandle(MarkerN_wait[break_num]);
        CloseHandle(MarkerN_console_stop[break_num]);
        CloseHandle(MarkerN_console_resume[break_num]);
    }

    DeleteCriticalSection(&struct_work);

    delete[] numbers;
    delete[] end_of_threads;
    delete[] hThread;
    delete[] MarkerN_console_resume;
    delete[] MarkerN_console_stop;
    delete[] MarkerN_wait;
    delete[] information.Arr; 

    return 0;
}