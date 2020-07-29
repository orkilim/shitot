#pragma once
#include "../Backend/Control.h"
#include "vector"

class Panel : public Control {
    protected:
        vector <Control*> Controlers;
        int focusedControlCell;

    public:
        Panel(short left, short top, short width, short height, Border* border, Color textColor= Color::White, Color backgroundColor = Color::Black) : Control(left, top, width, height, border, textColor, backgroundColor) {};
        ~Panel();
        
        void addToPanel(Control* controler);
        void draw(Graphics& g, int x, int y, size_t z);
        virtual void keyDown(int keyCode, char character);
        virtual void mousePressed(int x, int y, bool isLeft);
        int findFocusIndex();
        void updateFocusedControler(Control* controler);
        Control* getFirstControl();
        int getFocusedControlCell(){ return focusedControlCell; }
        bool canGetFocus() { return TRUE; };
        void getAllControls(vector<Control*>* controls);
};