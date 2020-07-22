#include <windows.h>
#include "TxtField.h"


int main(){
    TxtField tf(5,5,10,5);
    tf.setColors(FOREGROUND_BLUE|FOREGROUND_RED,BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY);
    tf.draw();
    while(1);
    return 0;
}