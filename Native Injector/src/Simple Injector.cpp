#include <iostream>
#include <Windows.h>
#include <string>
#include <random>

using namespace std;

void findProcId(const char* windowTitle, DWORD& pid) {

    GetWindowThreadProcessId(FindWindow(NULL, windowTitle), &pid);
}

bool fileExists(const string& fileName) {
    struct stat buffer;
    return (stat(fileName.c_str(), &buffer) == 0);
}

void setConsoleColor(unsigned char color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


string text = R"(
        _____  _      _          _____ _   _      _ ______ _____ _______ ____  _____  
       |  __ \| |    | |        |_   _| \ | |    | |  ____/ ____|__   __/ __ \|  __ \ 
       | |  | | |    | |          | | |  \| |    | | |__ | |       | | | |  | | |__) |
       | |  | | |    | |          | | | . ` |_   | |  __|| |       | | | |  | |  _  / 
       | |__| | |____| |____     _| |_| |\  | |__| | |___| |____   | | | |__| | | \ \ 
       |_____/|______|______|   |_____|_| \_|\____/|______\_____|  |_|  \____/|_|  \_)
                                             Made By Idkhidden
                                            github.com/idkhidden
    )";


int main() {    
    SetConsoleTitle(TEXT("Dll Injector | idkhiden"));
    cout << text << endl;

    cout << "[*] Enter The Process Name: ";
    string windowTitle;
    getline(cin, windowTitle);

    cout << "[*] Enter The DLL File Name: ";
    string dllName;
    getline(cin, dllName);

    system("CLS");
    cout << text << endl;

    DWORD procId = 0;
    char dllPath[MAX_PATH];

    cout << "[*] Process: " << windowTitle << endl;
    cout << "[*] DLL: " << dllName << endl; 
    cout << "-----------------------" << endl;

    findProcId(windowTitle.c_str(), procId);

    if (procId == 0) {
        setConsoleColor(FOREGROUND_RED);
        cout << "[*] Process Not Found" << endl;
    }
    else {
        setConsoleColor(FOREGROUND_GREEN);
        cout << "[*] Process Found" << endl;
    }

    if (!fileExists(dllName)) {
        setConsoleColor(FOREGROUND_RED);
        cout << "[*] DLL Not Found" << endl;
    }
    else {
        setConsoleColor(FOREGROUND_GREEN);
        cout << "[*] DLL Found" << endl;
    }

    if (!GetFullPathName(dllName.c_str(), MAX_PATH, dllPath, nullptr)) {
        setConsoleColor(FOREGROUND_RED);
        cout << "[*] Failed To Get Full Path" << endl;
    }
    else {
        setConsoleColor(FOREGROUND_GREEN);
        cout << "[*] Path Found" << endl;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

    if (!hProcess) {
        setConsoleColor(FOREGROUND_RED);
        cout << "[*] Failed To Open Process" << endl;
    }
    else {
        setConsoleColor(FOREGROUND_GREEN);
        cout << "[*] Process Opened" << endl;
    }

    void* allocatedMemory = VirtualAllocEx(hProcess, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    if (!allocatedMemory) {
        setConsoleColor(FOREGROUND_RED);
        cout << "[*] Failed Allocating Memory" << endl;
    }
    else {
        setConsoleColor(FOREGROUND_GREEN);
        cout << "[*] Memory Allocated" << endl;
    }

    if (!WriteProcessMemory(hProcess, allocatedMemory, dllPath, MAX_PATH, nullptr)) {
        setConsoleColor(FOREGROUND_RED);
        cout << "[*] Failed Writing to Memory" << endl;
    }
    else {
        setConsoleColor(FOREGROUND_GREEN);
        cout << "[*] Data Written to Memory" << endl;
    }

    HANDLE hThread = CreateRemoteThread(hProcess, nullptr, NULL, LPTHREAD_START_ROUTINE(LoadLibraryA), allocatedMemory, NULL, nullptr);

    if (!hThread) {
        setConsoleColor(FOREGROUND_RED);
        cout << "[*] Failed To Create Remote Thread" << endl;
    }
    else {
        setConsoleColor(FOREGROUND_GREEN);
        cout << "[*] Remote Thread Created" << endl;
    }

    CloseHandle(hProcess);
    VirtualFreeEx(hProcess, allocatedMemory, NULL, MEM_RELEASE);

    if (procId == 0 || !fileExists(dllName)) {
        setConsoleColor(FOREGROUND_RED);
        cout << "[*] DLL Not Injected" << endl;
        Sleep(500);
        cout << "[*] Exiting" << endl;
        Sleep(1000);
        exit(0);
    }
    else {
        setConsoleColor(FOREGROUND_GREEN);
        cout << "[*] DLL Injected" << endl;
        Beep(500, 1000);
        Sleep(500);
        cout << "[*] Exiting" << endl;
        Sleep(1000);
        exit(0);
        
    }

    system("pause");

    
}
