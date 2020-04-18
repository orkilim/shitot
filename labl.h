#include <String>
#include<windows.h>
#include<iostream>

using namespace std;

class Label{
string value;
COORD coord;
DWORD colors;

public:
    Label(string value, COORD coord):value(value),coord(coord){};

    void setValue(string value){this->value=value;}
    string getValue(){return this->value;}

    void setCoord(COORD coord){this->coord=coord;}
    COORD getCoord(){return this->coord;}

    void setColors(DWORD fg, DWORD bg)
    {
        this->colors=fg|bg;

    }

    void draw(){
        auto outHandle=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(outHandle,coord);
        SetConsoleTextAttribute(outHandle,colors);
        cout<<value;
        
        CONSOLE_CURSOR_INFO info={1,0};
        SetConsoleCursorInfo(outHandle,&info);
    }
};