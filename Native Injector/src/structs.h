#pragma once

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


