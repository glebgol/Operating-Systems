#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <cstdlib>

CRITICAL_SECTION criticalSection;

int main(int args, char* argv[]) {
    InitializeCriticalSection(&criticalSection);
    if (args == 2) {
        HANDLE Event = OpenEventA(EVENT_MODIFY_STATE, FALSE, argv[0]);
        HANDLE startEvent = OpenEventA(SYNCHRONIZE, FALSE, "StartSenderEvent");
        std::ofstream fout(argv[1], std::ios_base::binary | std::ios_base::out | std::ios_base::app);
        std::string message;
        SignalObjectAndWait(Event, startEvent, INFINITE, FALSE);
        bool ind = false;
        while (!ind) {
            printf("Input message to send or ");
            printf("0");
            printf(" to stop");
            std::cin >> message;
            if (strcmp("0", message.c_str()) != 0) {
                EnterCriticalSection(&criticalSection);
                fout << message << std::endl;
                SetEvent(Event);
                LeaveCriticalSection(&criticalSection);
            }
            else ind = true;
        }
        CloseHandle(startEvent);
        fout.close();
        CloseHandle(Event);
    }
    return 0;
}