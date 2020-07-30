#include "TextBox.h"
#include <iostream>
#include <algorithm>

TextBox::TextBox(short width, short top, short left, std::string value) : 
    width(width), top(top), left(left), value(value), cursor(value.length()), hasBorder(true),
    color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
    background(0), Label(value) {}

bool TextBox::keyDown(int keyCode, char charecter)
{

	int stringSize = static_cast<int>(value.size());

		if ((width - 2) > stringSize && (charecter >= 65 && charecter <= 90 || charecter >= 97 && charecter <= 122 || charecter >= 48 && charecter <= 57 || charecter == 32))
		{
			if (cursor < stringSize)
			{
				if (charecter == 32)
				{
					value.replace(value.begin() + cursor, value.end() - (stringSize - cursor), 1, charecter);
				}
				else
				{
					value.replace(value.begin() + cursor, value.end() - (stringSize - cursor), 1, charecter);
					cursor++;
				}
			}
			else
			{
				value.push_back(charecter);
				cursor = static_cast<int>(value.size());
			}
			return false;
		}
	else
	{
		switch (keyCode)
		{
		case VK_DELETE:
			if (cursor > 0)
			{
				value.erase(value.begin() + (cursor - 1));
				--cursor;
				return false;
			}
			break;
		case VK_BACK:
			if (cursor > 0)
			{
				value.erase(value.begin() + (cursor - 1));
				--cursor;
				return false;

			}
			break;
		case VK_LEFT:
			if (cursor > 0)
			{
				--cursor;
				return false;

			}
			break;
		case VK_NUMPAD4:
			if (cursor > 0)
			{
				--cursor;
				return false;

			}
		case VK_RIGHT:
			if (cursor < stringSize)
			{
				++cursor;
				return false;

			}
			break;
		case VK_NUMPAD6:
			if (cursor < stringSize)
			{
				++cursor;
				return false;

			}
			break;
		default:
			break;
		}
	}
	return true;
}

void TextBox::draw(Graphics& g, int x, int y, size_t z)
{
    COORD coord = { left, top };
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, color | (background << 4));
    
    std::cout << (char) 0xda;
    for (int i=0; i<width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xbf;

    SetConsoleCursorPosition(handle, {coord.X, coord.Y+1});
    std::cout << (char) 0xb3;
    
    for (int i =0; i < width; i++)
        std::cout << (i >= value.length() ? ' ' : value[i]);
    
    SetConsoleCursorPosition(handle, { left + width + 1, top + 1 });
    std::cout << (char) 0xb3;

    SetConsoleCursorPosition(handle, { left, top + 2 });
    std::cout << (char) 0xc0;
    for (int i = 0; i < width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xd9;
	int ff = static_cast<SHORT>(left + 1 + value.length());
	int uu = left + 1 + value.length();
	cursor;
    SetConsoleCursorPosition(handle, { static_cast<SHORT>(left + 1 + cursor), top+1 });
	if (this == focused && focus == true)
	g.setCursorVisibility(true);
	else
	g.setCursorVisibility(false);

}

void TextBox::mousePressed(int x, int y, bool isLeft)
{
	auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (x >= left && x <= left + width && y >= top && y <= top + 2 && isLeft == true)
	{
		if (this != focused || focus == false)
		{
			focus = true;
			focused = this;
		}
		if (value.size() >= x - left)
		{
			cursor = x - left;
		}
		else
			cursor = value.size();


	}
	else
		if (focus == true)
			focus = false;
}