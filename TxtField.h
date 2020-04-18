#include <String>
#include <windows.h>
#include <iostream>

HANDLE inHandle;
DWORD fdwSaveOldMode;
int placeInText = 1;
int rowNum = 0;
int textLength = 0;
short tbcX; //to be changed X
short tbcY; //to be changed Y
short originX;

using namespace std;

VOID ErrorExit(LPSTR lpszMessage)
{
    fprintf(stderr, "%s\n", lpszMessage);

    // Restore input mode on exit.

    SetConsoleMode(inHandle, fdwSaveOldMode);

    ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker, HANDLE out, int height, int length)
{

    if (ker.bKeyDown)
    {
        switch (ker.wVirtualKeyCode)
        {
        /*case VK_RETURN:
        {
            if (rowNum == height)
                break;
            tbcY++;
            SetConsoleCursorPosition(out, {originX, tbcY});
            tbcX = originX;
            textLength++;
            placeInText=textLength+1;
            rowNum++;
            break;
        }*/
        case VK_BACK:
        {
            if (tbcX == originX)
            {
                tbcX = originX + length - 1;
                tbcY--;
                SetConsoleCursorPosition(out, {tbcX, tbcY});
                cout << ' ';
                SetConsoleCursorPosition(out, {tbcX, tbcY});
                textLength--;
                rowNum--;
                placeInText = textLength + 1;
                break;
            }
            cout << '\b';
            cout << ' ';
            cout << '\b';
            tbcX--;
            textLength--;
            placeInText = textLength + 1;
            break;
        }
        case VK_LEFT:
        {
            if (tbcX <= originX)
            {
                if (rowNum == 0)
                    break;
                else
                {
                    tbcY--;
                    SetConsoleCursorPosition(out, {originX + length - 1, tbcY});
                    rowNum--;
                    tbcX = originX + length - 1;
                    break;
                }
            }
            tbcX--;
            SetConsoleCursorPosition(out, {tbcX, tbcY});
            placeInText--;
            break;
        }
        case VK_RIGHT:
        {
            if (placeInText > textLength)
                break;
            if (tbcX == originX + length - 1)
            {
                if (rowNum == height - 1)
                    break;
                else
                {
                    tbcY++;
                    SetConsoleCursorPosition(out, {originX, tbcY});
                    rowNum++;

                    tbcX = originX;
                    break;
                }
            }
            placeInText++;
            tbcX++;
            SetConsoleCursorPosition(out, {tbcX, tbcY});
            break;
        }
        default:
        {
            if (tbcX == originX + length - 1)
            {
                cout << ker.uChar.AsciiChar;
                tbcY++;
                SetConsoleCursorPosition(out, {originX, tbcY});
                tbcX = originX;
                rowNum++;
                textLength++;
                placeInText = textLength;
                break;
            }
            tbcX++;
            textLength++;
            placeInText = textLength + 1;
            cout << ker.uChar.AsciiChar;
            break;
        }
        }
    }
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
    printf("Mouse event: ");

    switch (mer.dwEventFlags)
    {
    case 0:

        if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            printf("left button press \n");
        }
        else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
        {
            printf("right button press \n");
        }
        else
        {
            printf("button press\n");
        }
        break;
    case DOUBLE_CLICK:
        printf("double click\n");
        break;
    case MOUSE_HWHEELED:
        printf("horizontal mouse wheel\n");
        break;
    case MOUSE_MOVED:
        printf("mouse moved\n");
        break;
    case MOUSE_WHEELED:
        printf("vertical mouse wheel\n");
        break;
    default:
        printf("unknown\n");
        break;
    }
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
    printf("Resize event\n");
    printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}

class TxtField
{
private:
    string value = "";
    short y;
    short x;
    DWORD colors;
    int length;
    int height;

public:
    TxtField(short x, short y, int length, int height) : x(x), y(y), length(length), height(height){};

    short getX() { return this->x; };
    short getY() { return this->y; };
    void setColors(DWORD fg, DWORD bg)
    {
        this->colors = fg | bg;
    }

    void draw()
    {
        DWORD cNumRead, fdwMode, i;
        INPUT_RECORD irInBuf[128];

        auto outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        inHandle = GetStdHandle(STD_INPUT_HANDLE);
        fdwMode = ENABLE_LINE_INPUT;
        SetConsoleMode(inHandle, fdwMode);
        SetConsoleCursorPosition(outHandle, {this->x, this->y});
        SetConsoleTextAttribute(outHandle, colors);
        short saveY = this->y;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < length; j++)
            {
                cout << " ";
            }
            SetConsoleCursorPosition(outHandle, {this->x, ++y});
        }
        SetConsoleCursorPosition(outHandle, {this->x, saveY});
        CONSOLE_CURSOR_INFO info = {1, 1};
        SetConsoleCursorInfo(outHandle, &info);
        COORD originalCoord = {this->x, this->y};
        char c;
        short Yloc = saveY;
        short Xloc = this->x;
        //int placeInValue = 0;
        //int placeInRow = 1;
        tbcX = this->x;
        originX = this->x;
        tbcY = saveY;
        while (1)
        {
            ReadConsoleInput(inHandle, irInBuf, 128, &cNumRead);
            for (i = 0; i < cNumRead; i++)
            {
                switch (irInBuf[i].EventType)
                {
                case KEY_EVENT: // keyboard input
                    KeyEventProc(irInBuf[i].Event.KeyEvent, outHandle, this->height, this->length);
                    break;

                case MOUSE_EVENT: // mouse input
                    MouseEventProc(irInBuf[i].Event.MouseEvent);
                    break;

                case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
                    ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
                    break;

                case FOCUS_EVENT: // disregard focus events

                case MENU_EVENT: // disregard menu events
                    break;

                default:
                    ErrorExit("Unknown event type");
                    break;
                }
            }
        }
    }
};

/*if (ker.bKeyDown)
    {
        switch (ker.wVirtualKeyCode)
        {
        case VK_RIGHT:
        {
            if (placeInRow >= textLength)
                break;
            if ((placeInRow >= length) && (rowNum >= height))
                break;
            if (placeInRow >= length)
            {
                SetConsoleCursorPosition(out, {x, ++y});
                placeInRow = 0;
                rowNum++;
                break;
            }

            SetConsoleCursorPosition(out, {++x, y});
            break;
        }
        case VK_LEFT:
        {
            if ((placeInRow <= 0) && (rowNum <= 0))
                break;
            if (placeInRow <= 0)
            {
                SetConsoleCursorPosition(out, {length, --y});
                placeInRow = length;
                rowNum--;
                break;
            }
            SetConsoleCursorPosition(out, {--x, y});
            break;
        }
        case VK_BACK:
        {
            if (textLength <= 0)
                break;
            if ((placeInRow <= 0) && (rowNum != 0))
            {
                SetConsoleCursorPosition(out, {length, --y});
                placeInRow = length;
                cout << ' ';
                rowNum--;
                break;
            }
            SetConsoleCursorPosition(out, {--x, y});
            cout << ' ';
            textLength--;
            placeInRow--;
            break;
        }
        case VK_RETURN:
        {
            if (rowNum >= height)
                break;
            SetConsoleCursorPosition(out, {x, ++y});
            break;
        }
        default:
        {
            if (placeInRow >= length)
            {
                textLength++;
                placeInRow = 0;
                rowNum++;
                SetConsoleCursorPosition(out, {x, ++y});
                cout << ker.uChar.AsciiChar;
                break;
            }
            cout << ker.uChar.AsciiChar;
            textLength++;
            ;
            break;
        }
        }
    }*/