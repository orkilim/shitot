#include "Button.h"

Button::Button(string value) : Label(value), clicked(FALSE), width(1), height(1){}
Button::Button(Border* _border, short _left, short _top, string _value) : Label(value) , clicked(FALSE), width(1), height(1)
{
    width = static_cast<int>(_value.size() + 2);
}

void Button::draw(Graphics& g, int x, int y, size_t z) { Label::draw(g, x, y, z); }

void Button::mousePressed(int x, int y, bool isLeft) {
    if (isInside(x, y, x, y, getWidth(), getHeight())) {
        for(int i = 0; i< Listeners.size(); i++){
            Listeners[i]->activateListener(x, y);
        }
    }
}

void Button::addListener(Listener* listener) {
    if(listener != nullptr)
        Listeners.push_back(listener);
}

//bool Button::keyDown(int keyCode, char character) {
//
//    if (keyCode == VK_DOWN)
//    {
//        if (curr == size - 1)
//        {
//            curr = 0;
//        }
//        else
//        {
//            ++curr;
//        }
//
//        for (auto& value : Panel::controls)
//        {
//            value->setTextColor(textColor);
//        }
//        temp = dynamic_cast<CheckBox*>(Panel::controls[curr]);
//        temp->setTextColor(Color::White);
//    }
//    this->flipBgToWhite();
//    clicked = TRUE;
//}
//
//
