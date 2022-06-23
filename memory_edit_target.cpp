// memory_edit_target.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

void plusplus(int& inc);
//a recursive function that exits the loop and closes the program when a true value is passed as a parameter
void programLoop(bool cont, int* targetVar) {
    if (!cont) {
        return;
    }
    std::cout << targetVar << ": " << *targetVar << std::endl;
    std::string trashString;
    std::cin >> trashString;
    plusplus(*targetVar);
    programLoop(true, targetVar);
}

void plusplus(int &inc) {
    inc++;
    return;
}

int target = 99;

int main()
{
    SetConsoleTitle(L"target");
    
    int* pTarget = &target;
    uintptr_t pEngine = (uintptr_t)GetModuleHandle(L"memory_edit_target.exe");
    std::cout << &target << "\ncalling loop" << std::endl;
    std::cout << "module base: " << std::hex << pEngine << std::endl;
    programLoop(true, pTarget);
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
