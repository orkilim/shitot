#include <iostream>
#include "string"
#include "Panel.h"
#include "vector"
#include "Label.h"
#include "Button.h"

struct position_t {short x; short y; };

class RadioBox : public Panel, public Listener {
    private:
        int left, top;
        vector<Button> options;
        vector<string> options_lbl;
        vector<position_t> options_pos;
        int cursor = -1;
        int selectedItem = -1;

    public:
        RadioBox(int left, int top, vector<string> options_lbl);
        void draw(Graphics& g, int x, int y, size_t z);
        bool keyDown(int keyCode, char character);
        void mousePressed(int x, int y, bool isLeft);
        void activateListener(int x, int y);
        bool SelectItemCursor(int index);
        bool ClearItemCursor();
        bool canGetFocus() { return TRUE; };
};