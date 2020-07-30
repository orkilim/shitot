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
    bool focus;
public:
    TextBox(short width, short top, short left, std::string value);
    void draw(Graphics& g, int x, int y, size_t z);
    virtual bool canGetFocus() { return TRUE; };
    bool keyDown(int keyCode, char charecter);
    void mousePressed(int x, int y, bool isLeft);
    string getText() { return value; }
    void setText(string text) { value = text; };
};