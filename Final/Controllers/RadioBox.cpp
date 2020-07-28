#include "RadioBox.h"
#include <fstream>

RadioBox::RadioBox(int left, int top, vector<string> options_lbl) : Panel(left, top, 20, 10, new Single, Color::White, Color::Red),
left(left),top(top),options_lbl(options_lbl)
{
    position_t pos = {0,0};
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
    }
}

void RadioBox::draw(Graphics& g, int x, int y, size_t z) {
    int controlerX, controlerY;
    if (!z)
        Panel::draw(g, x-1, y-1, z);
}

void RadioBox::keyDown(int keyCode, char character)
{
    ofstream myfile;
    myfile.open ("keyDown.txt", std::ios_base::app);
    myfile << "test" << endl;
    myfile.close();
}

void RadioBox::mousePressed(int x, int y, bool isLeft)
{
        for(int i=0; i < options_pos.size(); i++){
            if(x >= options_pos[i].x && x <= options_pos[i].x + 10 && y >= options_pos[i].y && isLeft == true)
            {
                if (selectedItem >= 0)
                ClearSelection();
                SelectedItem(i);
            }
        }
}

void RadioBox::activateListener(int x, int y)
{
    ofstream myfile;
    myfile.open ("activateListener.txt", std::ios_base::app);
    for(int i=0; i < options_pos.size(); i++){
        if(x >= options_pos[i].x && x <= options_pos[i].x + 10 && y >= options_pos[i].y)
        {
            if(selectedItem>=0)
            ClearSelection();
            SelectedItem(i);
        }
    }
    myfile.close();
}

bool RadioBox::SelectedItem(int index) {
    Color tempColor = options[index].getBackgroundColor();
    options[index].SetBackgroundColor(options[index].getTextColor());
    options[index].SetTextColor(tempColor);
    this->updateFocusedControler(this);
    selectedItem=index;
    return true;
}

bool RadioBox::ClearSelection() {
    Color tempColor = options[selectedItem].getBackgroundColor();
    options[selectedItem].SetBackgroundColor(options[selectedItem].getTextColor());
    options[selectedItem].SetTextColor(tempColor);
    this->updateFocusedControler(this);
    selectedItem = -1;
    return true;
}