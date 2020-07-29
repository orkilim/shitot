#include <iostream>
#include <string>
#include "Label.h"
#include <windows.h>

class TextBox : public Label
{
private:
    short width;
    short top;
    short left;
    short cursor;
    bool hasBorder;
    WORD color;
    WORD background;
    std::string value;
public:
    TextBox(short width, short top, short left, std::string value);
    void draw(Graphics& g, int x, int y, size_t z);
    virtual bool canGetFocus() { return true; };
    void handleKeyboardEvent(int keyCode, char charecter, Graphics& g);
    //void keyDown(int keyCode, char character);
    //void mousePressed(int x, int y, bool isLeft);
    string getText() { return value; }
    void setText(string text) { value = text; };
};