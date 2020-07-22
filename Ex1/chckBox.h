#include <String>
#include <windows.h>
#include <iostream>
#include "labl.h"

HANDLE inHandle;
DWORD fdwSaveOldMode;
int curr = 0;

VOID ErrorExit(LPSTR lpszMessage)
{
    fprintf(stderr, "%s\n", lpszMessage);

    // Restore input mode on exit.

    SetConsoleMode(inHandle, fdwSaveOldMode);

    ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker, COORD *coordArr, HANDLE out, int options, int *flag)
{

    if (ker.bKeyDown)
    {
        switch (ker.wVirtualKeyCode)
        {
        case VK_DOWN:
        {
            if (curr >= (options - 1))
                break;
            curr = curr + 1;
            SetConsoleCursorPosition(out, coordArr[curr]);

            break;
        }
        case VK_UP:
        {
            if (curr <= 0)
                break;
            curr = curr - 1;
            SetConsoleCursorPosition(out, coordArr[curr]);

            break;
        }
        case VK_SPACE:
        {
            if (flag[curr] == 1)
            {
                cout << ' ';
                SetConsoleCursorPosition(out, coordArr[curr]);
                flag[curr] = 0;
            }
            else
            {
                cout << 'V';
                SetConsoleCursorPosition(out, coordArr[curr]);
                flag[curr] = 1;
            }
            break;
        }
        case VK_RETURN:
        {
            if (flag[curr] == 1)
            {
                cout << ' ';
                SetConsoleCursorPosition(out, coordArr[curr]);
                flag[curr] = 0;
            }
            else
            {
                cout << 'V';
                SetConsoleCursorPosition(out, coordArr[curr]);
                flag[curr] = 1;
            }
            break;
        }
        default:
            break;
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

using namespace std;

class CheckBox
{
    int numOfOptions;
    short x;
    short y;
    DWORD colors;
    int *flagArr;

public:
    CheckBox(short x, short y, int num) : x(x), y(y), numOfOptions(num)
    {
        flagArr = new int[num];
    };

    void setColors(DWORD fg, DWORD bg)
    {
        this->colors = fg | bg;
    };

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
        short Xloc = (this->x) + 2;                      //x to be changed
        short Yloc = this->y;                            //y to be changed
        COORD *coordArr = new COORD[this->numOfOptions]; //an array of all the checkboxs' coordinates
        for (int i = 0; i < this->numOfOptions; i++)
        {
            coordArr[i] = {Xloc - 2, Yloc};
            cout << " ";
            SetConsoleCursorPosition(outHandle, {Xloc, Yloc});
            cout << "option " << (i + 1);
            Yloc = Yloc + 2;
            SetConsoleCursorPosition(outHandle, {this->x, Yloc});
        }
        CONSOLE_CURSOR_INFO info = {1, 1};
        SetConsoleCursorInfo(outHandle, &info);
        SetConsoleCursorPosition(outHandle, {this->x, this->y});
        char c;

        while (1)
        {
            ReadConsoleInput(inHandle, irInBuf, 128, &cNumRead);
            for (i = 0; i < cNumRead; i++)
            {
                switch (irInBuf[i].EventType)
                {
                case KEY_EVENT: // keyboard input
                    KeyEventProc(irInBuf[i].Event.KeyEvent, coordArr, outHandle, this->numOfOptions, this->flagArr);
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

/*while (1)
        {
            //c = getc(stdin);
        
            switch (c)
            {
            case 65: //up arrow key
            {
                if (currChkBox <= 0)
                    break;
                SetConsoleCursorPosition(outHandle, coordArr[--currChkBox]);

                break;
            }
            case 66: //down arrow key
            {
                if (currChkBox >= (this->numOfOptions) - 1)
                    break;
                SetConsoleCursorPosition(outHandle, coordArr[++currChkBox]);

                break;
            }
            case ' ': //space key
            {

                SetConsoleCursorPosition(outHandle, coordArr[currChkBox]);
                cout << 'V';
                SetConsoleCursorPosition(outHandle, coordArr[currChkBox]);
                break;
            }
            case '\n': //Enter key
            {
                SetConsoleCursorPosition(outHandle, coordArr[currChkBox]);
                cout << 'V';
                SetConsoleCursorPosition(outHandle, coordArr[currChkBox]);
                break;
            }
            default:
                if(c)
                    cout<<'\b';
                break;
            }
        }*/