#include "TextBox.h"
#include <iostream>
#include <algorithm>

TextBox::TextBox(short width, short top, short left, std::string value) : 
    width(width), top(top), left(left), value(value), cursor(value.length()), hasBorder(true),
    color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
    background(0), Label(value) {}

void TextBox::handleKeyboardEvent(int keyCode, char charecter, Graphics& g)
{
	int stringSize = static_cast<int>(value.size());

	g.moveTo(static_cast<int>(value.size()) + (left + 1), top + 1);
	if (charecter > 0)
	{
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

		}
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
			}
			break;
		case VK_BACK:
			if (cursor > 0)
			{
				value.erase(value.begin() + (cursor - 1));
				--cursor;
			}
		case VK_LEFT:
			if (cursor > 0)
			{
				--cursor;
			}
			break;
		case VK_NUMPAD4:
			if (cursor > 0)
			{
				--cursor;
			}
		case VK_RIGHT:
			if (cursor < stringSize)
			{
				++cursor;
			}
			break;
		case VK_NUMPAD6:
			if (cursor < stringSize)
			{
				++cursor;
			}
			break;
		}
	}





   /* if (!event.bKeyDown) return;

    if (event.wVirtualKeyCode >= 0x30 && event.wVirtualKeyCode <= 0x5a)
    {
        if (value.length() < width){
            value.insert(curserPosition, 1, event.uChar.AsciiChar);
            curserPosition++;
            draw();
        }
       
    }

    int textWidth = value.length();
    CONSOLE_SCREEN_BUFFER_INFO info;
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &info);
    auto offset = info.dwCursorPosition.X - this->left - 1;

    if (event.wVirtualKeyCode == VK_LEFT || event.wVirtualKeyCode == VK_RIGHT){
        if (offset > 0 && event.wVirtualKeyCode == VK_LEFT){
            SetConsoleCursorPosition(handle,{ info.dwCursorPosition.X - 1, info.dwCursorPosition.Y });
            curserPosition--;
        }
        if (offset < textWidth && event.wVirtualKeyCode == VK_RIGHT){
            SetConsoleCursorPosition(handle,{ info.dwCursorPosition.X + 1, info.dwCursorPosition.Y });
            curserPosition++;
        }
    }

    if (event.wVirtualKeyCode == VK_BACK)
    {
        if (value.length() > 0){
            value.erase(curserPosition - 1, 1);
            SetConsoleCursorPosition(handle,{ info.dwCursorPosition.X - curserPosition, info.dwCursorPosition.Y });
            curserPosition--;
            draw( this.g , top, top, top);
        }
    }*/
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

    SetConsoleCursorPosition(handle, { static_cast<SHORT>(left + 1 + value.length()), top+1 });
}

