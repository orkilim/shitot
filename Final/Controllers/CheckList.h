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
        int cursor=-1;
        bool focus;
        bool selectedItems[];
        bool SelectItemCursor(int index);
        bool ClearItemCursor();

    public:
        CheckList(int left, int top, vector<string> options_lbl);
        void draw(Graphics& g, int x, int y, size_t z);
        void mousePressed(int x, int y, bool isLeft);
        void activateListener(int x, int y);
        bool keyDown(int keyCode, char character);
        bool canGetFocus() { return TRUE; };
        bool isListObj() { return TRUE; }
        void onFocus(bool flag);
        bool AddSelectedItem(int index);
        bool RemoveSelectedItem(int index);
};