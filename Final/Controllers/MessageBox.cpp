#include "MessageBox.h"
#include <iostream>
#include <fstream>

MassageBox::MassageBox(string message) :
    Panel(0, 0, 1, 1, new Single, Color::Black, Color::Purple),
    ok(Button("<OK>")),
    cancel(Button("<Cancel>")),
    messageValue(Label(message)) {
        this->SetVisability(false);
        this->setWidth(ok.getWidth() + cancel.getWidth() + messageValue.getValue().length() + 4);
        this->setHeight(6);
        this->setLeft(2);
        this->setTop(2);
        messageValue.setTop(0);
        messageValue.setLeft(7);
        ok.setLeft(getLeft());
        ok.setTop(getHeight() - 3);
        cancel.setLeft(getWidth() - 10);
        cancel.setTop(getHeight() - 3);
        ok.addListener(this);
        cancel.addListener(this);
        this->addToPanel(&messageValue);
        this->addToPanel(&ok);
        this->addToPanel(&cancel);
}

void MassageBox:: draw(Graphics& g, int x, int y, size_t z){
    if (visible && !z){
        Control::lock_events();
        Panel::draw(g, x-1, y-1, z);
    }
    else if (!visible)
        Control::enable_events();
}

void MassageBox::mousePressed(int x, int y,bool isLeft){
   
    if (isInside(x,y, getLeft() + ok.getLeft() + 1, getTop() + ok.getTop() + 1, ok.getWidth(), ok.getHeight())){
        ok.mousePressed(x, y, isLeft);
    }
    else if (isInside(x,y, getLeft() + cancel.getLeft() + 1, getTop() + cancel.getTop() + 1, cancel.getWidth(), cancel.getHeight())){
        cancel.mousePressed(x, y, isLeft);
    }
}

void MassageBox::activateListener(int x, int y){
    if (visible) {
        if (isInside(x,y, getLeft() + ok.getLeft() + 1, getTop() + ok.getTop() + 1, ok.getWidth(), ok.getHeight())) {
            okPressed();
        }
        if (isInside(x,y, getLeft() + cancel.getLeft() + 1, getTop() + cancel.getTop() + 1, cancel.getWidth(), cancel.getHeight())) {
            cancelPressed();
        }
    }
    else {
        Control::lock_events();
    }
}

void MassageBox::okPressed(){
    this->SetVisability(false);
    buttonMsgValue = "OK";
    Control::enable_events();
}

void MassageBox::cancelPressed(){
    this->SetVisability(false);
    buttonMsgValue = "CANCEL";
    Control::enable_events();
}

void MassageBox::onFocus(bool flag)
{
    focus = flag;
}