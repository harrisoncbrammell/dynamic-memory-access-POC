// memory_edit_actor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <Tlhelp32.h>
#include <Psapi.h>

using namespace std;

DWORD getPIDWindowTitle(LPCSTR name) { //takes in window title and returns pid as dword
    DWORD pid;
    HWND windowHandle = FindWindowA(NULL, name);
    GetWindowThreadProcessId(windowHandle, &pid);
    if (pid) { //We test the DWORD we declared.
        cout << "Process ID is: " << pid << endl; // If true, we cout the process id
    }
    else {
        cout << "Unable to find the process id !" << endl;
    }
    return pid;
}

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

int readInt(DWORD pidArg) {
    HANDLE hTarget = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pidArg);
    SIZE_T num;
    int readValue;
    uintptr_t targetaddress = GetModuleBaseAddress(getPIDWindowTitle("target"), L"memory_edit_target.exe")+0x5044;
    ReadProcessMemory(hTarget, (void*)targetaddress, &readValue, sizeof(readValue), &num);
    std::cout << readValue << std::endl;
    return readValue;
}

void programLoop() {
    readInt(getPIDWindowTitle("target"));
    std::string garabage;
    std::cin >> garabage;
    programLoop();
}

int main() //toolhelp32api
{
    uintptr_t serverdllBaseAddress = GetModuleBaseAddress(getPIDWindowTitle("target"), L"memory_edit_target.exe");
    std::cout << "base address: " << std::hex << serverdllBaseAddress << std::endl;
    programLoop();
	return 0;
}
