#include <windows.h>
#include "labl.h"


int main(){
    Label l("hello world",{5,5});
    l.setColors(FOREGROUND_BLUE|FOREGROUND_RED,BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY);
    l.draw();
    while(1);
    return 0;
}