#include "CheckList.h"
#include <fstream>
/* newwwwwwwww*/
CheckList::CheckList(int left, int top, vector<string> options_lbl) : Panel(left, top, 20, 10, new Single, Color::Black, Color::Green),
left(left),top(top),options_lbl(options_lbl)
{
    position_s pos = {0,0};
    for (std::vector<string>::iterator lbl = options_lbl.begin() ; lbl != options_lbl.end(); ++lbl)
    {
        options.push_back(Button(*lbl));
    }
    for(int i=0; i < options.size(); i++ )
    {
        options[i].setTop(i);
        options[i].addListener(this);
        this->addToPanel(&options[i]);
        pos.x = getLeft();
        pos.y = getTop()+i+1;
        options_pos.push_back(pos);
        selectedItem[i] = FALSE;
    }
}

void CheckList::draw(Graphics& g, int x, int y, size_t z) {
    int controlerX, controlerY;
    if (!z)
        Panel::draw(g, x-1, y-1, z);
}


void CheckList::mousePressed(int x, int y, bool isLeft)
{
    int u, t;
    for (int i = 0; i < options_pos.size(); i++) {
        if (x >= options_pos[i].x && x <= options_pos[i].x + 10 && y == options_pos[i].y && isLeft == true)
        {
            if (selectedItem[i] == FALSE)
            {
                AddSelectedItem(i);
            }
            else
                RemoveSelectedItem(i);
        }
    }

}
