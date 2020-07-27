#include "CheckList.h"
#include <fstream>
/*newwwwwwwwwwwwwwwwwwwwwwwwwwwwww*/
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

void CheckList::activateListener(int x, int y)
{
    ofstream myfile;
    myfile.open ("activateListener.txt", std::ios_base::app);
    for(int i=0; i < options_pos.size(); i++){
        if(x >= options_pos[i].x && x <= options_pos[i].x + 10 && y >= options_pos[i].y)
        {
            AddSelectedItem(i);
        }
    }
    myfile.close();
}

bool CheckList::AddSelectedItem(int index) {
    if (selectedItem[index] == FALSE)
    {
        Color tempColor = options[index].getBackgroundColor();
        options[index].SetBackgroundColor(options[index].getTextColor());
        options[index].SetTextColor(tempColor);
        this->updateFocusedControler(this);
        selectedItem[index] = TRUE;
        return TRUE;
    }
    return FALSE;
}

bool CheckList::RemoveSelectedItem(int index) {
    if (selectedItem[index] == TRUE)
    {
        Color tempColor = options[index].getBackgroundColor();
        options[index].SetBackgroundColor(options[index].getTextColor());
        options[index].SetTextColor(tempColor);
        this->updateFocusedControler(this);
        selectedItem[index] == FALSE;
        return TRUE;
    }
    return FALSE;
}

//void CheckList::keyDown(int keyCode, char charecter, Graphics& g)
//{
//	int vectorSize = static_cast<int>(options_pos.size());
//
//	switch (keyCode)
//	{
//		//tab was pressed
//	case VK_TAB:
//		// if no focused
//		if (++currentCboxIndex == 0)
//		{
//			selectedItemkey[] = currentCboxIndex;
//			checkBoxs[currentCboxIndex]->flipBgToWhite();
//		}
//		// if is in last position befor out of the check list
//		else if (currentCboxIndex == vectorSize - 1)
//		{
//			options_pos[currentCboxIndex - 1]->flipBgToBlack();
//			options_pos[currentCboxIndex]->flipBgToWhite();
//			selectedItemkey = currentCboxIndex;
//		}
//		// middle
//		else
//		{
//			options_pos[currentCboxIndex - 1]->flipBgToBlack();
//			options_pos[currentCboxIndex]->flipBgToWhite();
//			selectedItemkey = currentCboxIndex;
//		}
//		break;
//
//		//key down was pressed
//	case VK_DOWN:
//		// if no focused
//		if (++currentCboxIndex == 1)
//		{
//			options_pos[currentCboxIndex - 1]->flipBgToBlack();
//			options_pos[currentCboxIndex]->flipBgToWhite();
//			selectedItemkey = currentCboxIndex;
//		}
//		else if (currentCboxIndex == 0)
//		{
//			options_pos[currentCboxIndex]->flipBgToWhite();
//			selectedItemkey = currentCboxIndex;
//		}
//		// if is in last position befor out of the check list
//		else if (currentCboxIndex == vectorSize)
//		{
//			//options_pos[currentCboxIndex - 1]->flipBgToBlack();
//			//options_pos[0]->flipBgToWhite();
//			currentCboxIndex = 0;
//			selectedItemkey = currentCboxIndex;
//		}
//		// middle
//		else
//		{
//			options_pos[currentCboxIndex - 1]->flipBgToBlack();
//			options_pos[currentCboxIndex]->flipBgToWhite();
//			selectedItemkey = currentCboxIndex;
//		}
//		break;
//
//		//numpad2 was pressed like key down
//	case VK_NUMPAD2:
//		// if no focused
//		if (++currentCboxIndex == 1)
//		{
//			options_pos[currentCboxIndex - 1]->flipBgToBlack();
//			options_pos[currentCboxIndex]->flipBgToWhite();
//			selectedItemkey = currentCboxIndex;
//		}
//		else if (currentCboxIndex == 0)
//		{
//			options_pos[currentCboxIndex]->flipBgToWhite();
//			selectedItemkey = currentCboxIndex;
//		}
//		// if is in last position befor out of the check list
//		else if (currentCboxIndex == vectorSize)
//		{
//			options_pos[currentCboxIndex - 1]->flipBgToBlack();
//			options_pos[0]->flipBgToWhite();
//			currentCboxIndex = 0;
//			selectedItemkey = currentCboxIndex;
//		}
//		// middle
//		else
//		{
//			options_pos[currentCboxIndex - 1]->flipBgToBlack();
//			options_pos[currentCboxIndex]->flipBgToWhite();
//			selectedItemkey = currentCboxIndex;
//		}
//		break;
//
//		//key up was pressed
//	case VK_UP:
//		// if no focused
//		if (--currentCboxIndex == 0)
//		{
//			options_pos[currentCboxIndex + 1]->flipBgToBlack();
//			options_pos[currentCboxIndex]->flipBgToWhite();
//			selectedItemkey = currentCboxIndex;
//		}
//		else if (currentCboxIndex <= -1)
//		{
//			currentCboxIndex = vectorSize - 1;
//			options_pos[0]->flipBgToBlack();
//			options_pos[currentCboxIndex]->flipBgToWhite();
//			selectedItemkey = currentCboxIndex;
//		}
//		// if is in last position befor out of the check list
//		// middle
//		else
//		{
//			options_pos[currentCboxIndex]->flipBgToWhite();
//			options_pos[currentCboxIndex + 1]->flipBgToBlack();
//			selectedItemkey = currentCboxIndex;
//		}
//		break;
//
//		//numpad 8 was pressed like key up
//	case VK_NUMPAD8:
//		// if no focused
//		if (--currentCboxIndex == 0)
//		{
//			options_pos[currentCboxIndex + 1]->flipBgToBlack();
//			options_pos[currentCboxIndex]->flipBgToWhite();
//			selectedItemkey = currentCboxIndex;
//		}
//		else if (currentCboxIndex <= -1)
//		{
//			currentCboxIndex = vectorSize - 1;
//			options_pos[0]->flipBgToBlack();
//			options_pos[currentCboxIndex]->flipBgToWhite();
//			selectedItemkey = currentCboxIndex;
//		}
//		// if is in last position befor out of the check list
//		// middle
//		else
//		{
//			options_pos[currentCboxIndex]->flipBgToWhite();
//			options_pos[currentCboxIndex + 1]->flipBgToBlack();
//			selectedItemkey = currentCboxIndex;
//		}
//		break;
//
//		//space button was pressed to select current item and check it
//	case VK_SPACE:
//
//		options_pos[selectedItemkey]->setIsSelected();
//		break;
//
//	}
//}

//return true if the checklist focus is on last child
bool CheckList::getIsInLastChild()
{
	int vectorSize = static_cast<int>(options_pos.size());
	// if no focused
	if (++currentCboxIndex == 0)
	{
		selectedItemkey = currentCboxIndex;
		//options_pos[currentCboxIndex]->flipBgToWhite();
		return FALSE;
	}
	// if is in last position befor out of the check list
	else if (currentCboxIndex == vectorSize - 1)
	{
		//options_pos[currentCboxIndex]->flipBgToWhite();
		//options_pos[currentCboxIndex - 1]->flipBgToBlack();
		currentCboxIndex = vectorSize - 1;
		selectedItemkey = currentCboxIndex;
		return FALSE;
	}
	else if (currentCboxIndex == vectorSize)
	{
		//options_pos[vectorSize - 1]->flipBgToBlack();
		currentCboxIndex = -1;
		return TRUE;
	}
	// middle
	else
	{
		//options_pos[currentCboxIndex - 1]->flipBgToBlack();
		//options_pos[currentCboxIndex]->flipBgToWhite();
		selectedItemkey = currentCboxIndex;
		return FALSE;
	}

}

//set focus method
void CheckList::onFocus(bool flag)
{
	focus = flag;
}