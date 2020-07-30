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

        void setMessageValue(string messageValue) { this->messageValue.setValue(messageValue); }
        string getMessageValue() { return messageValue.getValue(); }
            
        void setOKText(string ok) { this->ok = ok; }
        void setCancelText(string cancel) { this->cancel = cancel; }
            
        void setValue(string message) { this->buttonMsgValue = message; }
        string getValue(){ return this->buttonMsgValue; }

        void draw(Graphics& g, int x, int y, size_t z);
        bool keyDown(int keyCode, char character);
        void mousePressed(int x, int y, bool isLeft);
        void activateListener(int x, int y);
        virtual void okPressed();
        virtual void cancelPressed();
        bool canGetFocus() { return TRUE; };
        void onFocus(bool flag);
};