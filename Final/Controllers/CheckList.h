#include <iostream>
#include "string"
#include "Panel.h"
#include "vector"
#include "Label.h"
#include "Button.h"

struct position_s {short x; short y; };

class CheckList : public Panel, public Listener {
    private:
        int left, top;
        vector<Button> options;
        vector<string> options_lbl;
        vector<position_s> options_pos;
        int currentCboxIndex;
        int selectedItemkey=0;
        bool focus;
        bool selectedItem[];
       
    public:
        CheckList(int left, int top, vector<string> options_lbl);
        void draw(Graphics& g, int x, int y, size_t z);
        void mousePressed(int x, int y, bool isLeft);
        void activateListener(int x, int y);
        bool AddSelectedItem(int index);
        bool RemoveSelectedItem(int index);
        bool getIsInLastChild();
        void keyDown(int keyCode, char charecter, Graphics& g);
        bool canGetFocus() { return TRUE; };
        bool isListObj() { return TRUE; }
        void onFocus(bool flag);
};