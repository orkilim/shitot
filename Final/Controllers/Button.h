#pragma once
#include "Label.h"
#include <iostream>
#include "string"
#include "Listener.h"

class Button : public Label {
    private:
        string value;
        int width;
        int height;
        bool clicked;
        vector <Listener*> Listeners;

    public:
        Button(string value);
        Button(Border* _border, short _left, short _top, string val);
        bool canGetFocus() { return FALSE; };
        void addListener(Listener* listner);
        void mousePressed(int x, int y, bool isLeft);
        void draw(Graphics& g, int x, int y, size_t z);
        void Clicked() { clicked = true; };
        void UnClicked() { clicked = false; };
        bool CkClicked() { return clicked; };
        ~Button() {};
};