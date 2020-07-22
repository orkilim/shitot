#include <windows.h>
#include "chckBox.h"


int main(){
    CheckBox cb(5,5,4);
    cb.setColors(FOREGROUND_BLUE|FOREGROUND_RED,BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY);
    cb.draw();
    return 0;
}