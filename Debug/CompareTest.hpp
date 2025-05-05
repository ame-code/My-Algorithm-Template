#pragma once
#ifndef COMPARETEST_HEADER
#define COMPARETEST_HEADER

#include<cstdlib>
#include<string>

namespace aleaf {
    void compareTest(std::string ansCode, std::string myCode, std::string dataCode) {
        const std::string codeFileName[3] = {ansCode, myCode, dataCode};
        std::string compileCommand = "g++ -fdiagnostics-color=always -Wall -Werror -std=c++20 CodeFileName -o ";
        const std::string exeFileName[3] = {"ansCode.exe", "myCode.exe", "dataCode.exe"};
        for(auto str : codeFileName) {
            system(std::string(compileCommand).replace(compileCommand.find("CodeFileName"), 12, str).c_str());
        }
        while(true) {
            system((dataCode + " > data.txt").c_str());
            system((ansCode + " < data.txt > ansCode.txt").c_str());
            system((myCode + " < data.txt  > myCode.txt").c_str());
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

#endif