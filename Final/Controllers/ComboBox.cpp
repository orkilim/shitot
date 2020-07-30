#include "ComboBox.h"
#include <fstream>
#include <math.h>

ComboBox::ComboBox(int left, int top, vector<string> options_lbl) : Panel(left, top, 25, 13, new Single, Color::Red, Color::White),
left(left), top(top), options_lbl(options_lbl), focus(false), valueToDisplay("ComboBox"),
closeHeight(5), isOpen(false), selectedItem(0) {
	position_c pos = { 0,0 };
	for (std::vector<string>::iterator lbl = options_lbl.begin(); lbl != options_lbl.end(); ++lbl)
	{
		options.push_back(Button(*lbl));
	}
	for (int i = 0; i < options.size(); i++)
	{
		options[i].setTop(i);
		options[i].addListener(this);
		this->addToPanel(&options[i]);
		pos.x = getLeft();
		pos.y = getTop() + i + 1;
		options_pos.push_back(pos);
	}
}

void ComboBox::draw(Graphics & g, int x, int y, size_t z) {
	int vectorSize = static_cast<int>(options.size());
	g.moveTo(x, y);


	if (!isOpen)//close
	{
		if (this == focused)
		{ 
			focus = true;
			g.setBackground(Color::Black);
}
		if (focus && cursor == -1)
			cursor++;
		cout << '\xDA';
		for (int i = 0; i < 22; i++)
		{
			cout << '\xC4';
		}
		cout << '\xBF';
		g.moveTo(x, y + 1);
		cout << '\xB3';
		for (int i = 0; i < 20; i++)
		{
			cout << ' ';
		}
		cout << '\xB3' << '\xF0' << '\xB3';
		g.write(x + 2, y + 1, valueToDisplay);
		g.moveTo(x, y + 2);
		cout << '\xC0';
		for (int i = 0; i < 22; i++)
		{
			cout << '\xC4';
		}
		cout << '\xD9';
	}
	else
	{
		cout << '\xDA';
		for (int i = 0; i < 22; i++)
		{
			cout << '\xC4';
		}
		cout << '\xBF';
		g.moveTo(x, y + 1);
		cout << '\xB3';
		for (int i = 0; i < 20; i++)
		{
			cout << ' ';
		}
		cout << '\xB3' << '\xF0' << '\xB3';
		g.write(x + 2, y + 1, options_lbl[0]);
		g.moveTo(x, y + 2);
		cout << '\xB3';
		for (int i = 0; i < 22; i++)
		{
			cout << '\xC4';
		}
		cout << '\xB3';


		int tempX = x;
		int tempY = y + 3;

		for (int y = 0; y < vectorSize; y++)
		{
			g.setBackground(backgroundColor);
			g.setForeground(textColor);
			if (y == selectedItem)
			{
				g.setBackground(Color::White);
				g.setForeground(Color::Black);
			}
			if (y == vectorSize - 1)
			{
				g.moveTo(tempX, tempY);
				cout << '\xB3';
				for (int x = 0; x < 22; x++)
				{
					cout << ' ';
				}
				cout << '\xB3';
				g.write(tempX + 2, tempY, options_lbl[y]);
				g.moveTo(tempX, ++tempY);
				cout << '\xC0';
				for (int x = 0; x < 22; x++)
				{
					cout << '\xC4';
				}
				cout << '\xD9';
			}
			else
			{
				g.moveTo(tempX, tempY);
				cout << '\xB3';
				for (int x = 0; x < 22; x++)
				{
					cout << ' ';
				}
				cout << '\xB3';
				g.write(tempX + 2, tempY, options_lbl[y]);
				g.moveTo(tempX, ++tempY);
				cout << '\xB3';
				for (int x = 0; x < 22; x++)
				{
					cout << '\xC4';
				}
				cout << '\xB3';
				tempY++;
			}

		}
	}
}

void ComboBox::mousePressed(short x, short y, bool isLeft) {


	if (!isOpen)
	{
		if (y == top + 1 && (x > left && x < (left + width) && !options[0].CkClicked()))//39-62, 3-7
		{
			isOpen = !isOpen;
		}

	}
	else
	{
		if (y >= top && y <= top + 3 && (x > left && x < (left + width)))
		{
			if (!options[0].CkClicked())
				isOpen = !isOpen;
		}
		else
		{
			

			y = ceil(float(y) / 2);
			int tempY = y - 4;
			if (y== options_pos[tempY].y)
			{
			selectedItem = tempY;
			valueToDisplay = options_lbl[tempY];
			isOpen = !isOpen;
 }
		}

	}
}

void ComboBox::activateListener(int x, int y)
{
	if (x >= options_pos[0].x && x <= options_pos[0].x + 24 && y >= options_pos[0].y - 1 && y <= top + options_pos.size() * 3)
	{

		if (!isOpen)//close
		{

			if (y <= options_pos[0].y + 2 || y >= options_pos[0].y + 2)
				mousePressed(x, options_pos[0].y, left);

		}
		else //open
		mousePressed(x, y, left);

	}
	if (options[options_pos.size() - 2].CkClicked())
	{
		for (int i = 0; i < options_pos.size(); i++)
			options[i].UnClicked();
	}
}

ComboBox::~ComboBox()
{
	/*Panel::~Panel();
	free(choosenItem);
	free(toogleBtn);*/
}

bool ComboBox::keyDown(int keyCode, char character)
{		
	if (keyCode == VK_TAB)
	{ 
			return true;
			focused = NULL;
}
		if (keyCode == VK_SPACE || keyCode == VK_RETURN)
		{
			isOpen=!isOpen;
		}
		//if (isOpen)
		//return false;

		return false;
}
