#pragma once

#ifndef CMDINFO_H
#define CMDINFO_H

#include <iostream>
#include <windows.h>
#include <string>

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int digits(int n) {
    return std::to_string(n).size();
}

class cmdinfo {
    private:
        int points = 25;
        int progress = 0;

    public:
        cmdinfo(){}

        void update(int p){
            ShowConsoleCursor(false);

            progress = p;

            std::cout <<'[';

            for(int i = 1; i <= 25; i++) {
                if(i <= progress/4) std::cout << '#';
                else                std::cout << '-';
            }

            std::cout << "] " << progress << '%';

            if(progress != 100) for(int i = 0; i < 29 + digits(progress); i++) std::cout <<'\b';
            else {
                std::cout << '\n';
                ShowConsoleCursor(true);
            } 

            
        }

};

#endif