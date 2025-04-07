#pragma once

#include<bits/stdc++.h>

namespace Debug {
    void initializeRand() {
        srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
    }

    void compareTest(std::string ansCode, std::string myCode, std::string dataCode) {
        const std::string codeFileName[3] = {ansCode, myCode, dataCode};
        std::string compileCommand = "g++ -fdiagnostics-color=always -Wall -Werror -std=c++20 CodeFileName -o ";
        const std::string exeFileName[3] = {"ansCode.exe", "myCode.exe", "dataCode.exe"};
        for(auto str : codeFileName) {
            system(std::string(compileCommand).replace(compileCommand.find("codeFileName"), 12, str).c_str());
        }
        initializeRand();
        while(true) {
            system((dataCode + " > data.txt").c_str()), system((ansCode + " < data.txt > ansCode.txt").c_str()), system((myCode + " < data.txt  > myCode.txt").c_str());
            #ifdef __WIN32
            if(system("fc ansCode.txt myCode.txt")) {
                break;
            }
            #else defined(__linux__)
            if(system("diff ansCode.txt myCode.txt")) {
                break;
            }
            #endif
        }
    }
}