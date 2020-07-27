#pragma once
#include <string>
#include "Button.h"
#include "../Backend/Border/Border.h"
#include "Panel.h"

class MassageBox : public Panel, public Listener {
    protected:
        Button ok;
        Button cancel;
        Label messageValue;
        string buttonMsgValue;
        bool focus;

    public:
        MassageBox(string message);
        ~MassageBox() {}



        void draw(Graphics& g, int x, int y, size_t z);

        void mousePressed(int x, int y, bool isLeft);
        
};