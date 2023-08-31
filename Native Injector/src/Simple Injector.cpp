#include <iostream>
#include <Windows.h>
#include <thread>
#include <libloaderapi.h>
#include <string>

using namespace std;

void find_proc_id(const char* window_title, DWORD &pid) 
    {
        GetWindowThreadProcessId(FindWindow(NULL, window_title), &pid);
    }

bool file(string file_name)
    {
    struct stat buffer;
    return(stat(file_name.c_str(), &buffer) == 0);
    }
void setcolor(unsigned char color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}



int main()
{   
    
    string text =
        "                 _____  _      _          _____ _   _      _ ______ _____ _______ ____  _____  \n"
        "                |  __ \\| |    | |        |_   _| \\ | |    | |  ____/ ____|__   __/ __ \\|  __ \\ \n"
        "                | |  | | |    | |          | | |  \\| |    | | |__ | |       | | | |  | | |__) |\n"
        "                | |  | | |    | |          | | | . ` |_   | |  __|| |       | | | |  | |  _  / \n"
        "                | |__| | |____| |____     _| |_| |\\  | |__| | |___| |____   | | | |__| | | \\ \\ \n"
        "                |_____/|______|______|   |_____|_| \\_|\\____/|______\\_____|  |_|  \\____/|_|  \\_\\\n"
        "                                                                                \n"
        "                  "
        "                             Made By Idkhidden\n"
        "                                              github.com/idkhidden\n"
        "\n";

    SetConsoleTitle(TEXT("DLL Injector | idkhidden"));
     
    cout << text;

    cout << "[*] Enter The Process Name: ";
    string window_title;
    getline(cin, window_title);

    cout << "[*] Enter The DLL File Name: ";
    string dll_name;
    getline(cin, dll_name);

    system("CLS");
    
    
    cout << text;
    
    DWORD proc_id = NULL;
    char dll_path[MAX_PATH];
        
   
    cout << "[*] Process: " << window_title << ".exe" << endl;
    cout << "[*] DLL: " << dll_name << endl;
    cout << "\n";
 
    find_proc_id(window_title.c_str(), proc_id);
    if (proc_id == NULL)
    {   
        setcolor(FOREGROUND_RED);
        cout << "[*] Process Not Found" << endl;

    }
    else
    {
        setcolor(FOREGROUND_GREEN);
        cout << "[*] Process Found" << endl;
    }
    if (!file(dll_name))
    {
        setcolor(FOREGROUND_RED);
        cout << "[*] DLL Not Found" << endl;

    }
    else
    {
        setcolor(FOREGROUND_GREEN);
        cout << "[*] DLL Found" << endl;
    }

    if (!GetFullPathName(dll_name.c_str(), MAX_PATH, dll_path, nullptr))
    {
        setcolor(FOREGROUND_RED);
        cout << "[*] Failed To Get Full Path";

    }
    else
    {
        setcolor(FOREGROUND_GREEN);
        cout << "[*] Path Found" << endl;
    }
    HANDLE Hprocess = OpenProcess(PROCESS_ALL_ACCESS, NULL, proc_id);
    if (!Hprocess)
    {
        setcolor(FOREGROUND_RED);
        cout << "[*] Failed To Get Open Process" << endl;

    }
    else
    {
        setcolor(FOREGROUND_GREEN);
        cout << "[*] Open Process Found" << endl;
    }
    void* allocated_memory = VirtualAllocEx(Hprocess, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!allocated_memory)
    {
        setcolor(FOREGROUND_RED);
        cout << "[*] Failed Getting VirtualAlloc" << endl;
    }
    else

    {
        setcolor(FOREGROUND_GREEN);
        cout << "[*] VirtualAloc Found" << endl;
    }
    if (!WriteProcessMemory(Hprocess, allocated_memory, dll_path, MAX_PATH, nullptr))
    {
        setcolor(FOREGROUND_RED);
        cout << "[*] Failed To Get WPM" << endl;

    }
    else
    {
        setcolor(FOREGROUND_GREEN);
        cout << "[*] WPM Found" << endl;
    }
    HANDLE Hthread = CreateRemoteThread(Hprocess, nullptr, NULL, LPTHREAD_START_ROUTINE(LoadLibraryA), allocated_memory, NULL, nullptr);
    if (!Hthread)
    {
        setcolor(FOREGROUND_RED);
        cout << "[*] Failed To Get Remote Thread" << endl;

    }
    else
    {
        setcolor(FOREGROUND_GREEN);
        cout << "[*] Remote Thread Found" << endl;
    }
    CloseHandle(Hprocess);
    VirtualFreeEx(Hprocess, allocated_memory, NULL, MEM_RELEASE);
    if (proc_id == NULL | !file(dll_name))
    {
        setcolor(FOREGROUND_RED);
        cout << "[*] DLL Not Injected" << endl;
    }
    else
    {
        setcolor(FOREGROUND_GREEN);
        cout << "[*] DLL Injected" << endl;
    }
    system("pause");

 
}

