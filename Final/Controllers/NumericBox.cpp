#include "NumericBox.h"

NumericBox::NumericBox
    (int minVal, int maxVal, short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor) :
    Panel(left, top, width, height, border, textColor, backgroundColor),
    inc(Button("+")), 
    dec(Button("-")),
    minVal(minVal),
    maxVal(maxVal),
    value(Label(std::to_string((minVal + maxVal) / 2))) {
        val = (minVal + maxVal) / 2;
        if(val>=0)
        value.setLeft(this->dec.getValue().length() + 1);
        else
        value.setLeft(this->dec.getValue().length());
        inc.setLeft(to_string(maxVal).length() + 1 + 2);
        this->setWidth(inc.getLeft() + 1);
        this->inc.addListener(this);
        this->dec.addListener(this);
        this->addToPanel(&dec);
        this->addToPanel(&value);
        this->addToPanel(&inc);
}

void NumericBox::draw(Graphics& g, int x, int y, size_t z) {
    if (!z)
        Panel::draw(g, x-1, y-1, z);
}

void NumericBox::activateListener(int x, int y){   
    if ((getLeft() + inc.getLeft() + 1 == x) && (getTop() + inc.getTop() + 1 == y)) {
        if (val < maxVal){
            value.setValue(std::to_string(++val));
            if (val >= 0)
                value.setLeft(this->dec.getValue().length() + 1);
            else
                value.setLeft(this->dec.getValue().length() );
        }    
    }
    else if ((getLeft() + dec.getLeft() + 1 == x) && (getTop() + dec.getTop() + 1 == y)) {
        if (val > minVal) {
            value.setValue(std::to_string(--val));
            if (val >= 0)
                value.setLeft(this->dec.getValue().length() + 1);
            else
                value.setLeft(this->dec.getValue().length() );
        }
    }
}

void NumericBox::mousePressed(int x, int y, bool isLeft){
        if (isInside(x,y, getLeft() + inc.getLeft() + 1, getTop() + inc.getTop() + 1, getWidth() + inc.getWidth(), getHeight() + inc.getHeight())){
            inc.mousePressed(x, y, isLeft);
        }
        else if (isInside(x,y, getLeft() + dec.getLeft() + 1, getTop() + dec.getTop() + 1, getWidth() + dec.getWidth(), getHeight() + dec.getHeight())){
            dec.mousePressed(x, y, isLeft);
        }
}

void NumericBox::onFocus(bool flag)
{
    focus = flag;

}

//void NumericBox::keyDown(int keyCode, char charecter, Graphics& g)
//{
//    switch (keyCode)
//    {
//    case VK_DELETE:
//        value = 0;
//        break;
//    case VK_LEFT:
//        value++;
//        break;
//    case VK_NUMPAD4:
//        value++;
//    case VK_RIGHT:
//        if (value == 0) {
//            break;
//        }
//        value--;
//        break;
//    case VK_NUMPAD6:
//        if (value == 0) {
//            break;
//        }
//        value--;
//        break;
//    }
//}
