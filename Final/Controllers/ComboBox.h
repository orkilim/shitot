#pragma once
#include <iostream>
#include "string"
#include "Panel.h"
#include "vector"
#include "Label.h"
#include "Button.h"

struct position_c { short x; short y; };

class ComboBox : public Panel, public Listener
{
	int left, top;
	vector<Button> options;
	vector<string> options_lbl;
	vector<position_c> options_pos;
	int cursor = -1;
	int selectedItem = -1;
	bool isOpen;
	int openHeight, closeHeight;
	bool focus;
	string valueToDisplay;


	void onDownKey();
	void onUpKey();
	void onEnterKey();
	bool SelectItemCursor(int index);
	bool ClearItemCursor();

public:
	ComboBox(int left, int top, vector<string> options_lbl);
	size_t getSelectedIndex();
	void setSelectedIndex(size_t);
	void draw(Graphics& g, int x, int y, size_t z);
	void mousePressed(short x, short y, bool isLeft);
	void toggle();
	void unfocus();
	void openList();
	void closeList();
	void activateListener(int x, int y);
	bool keyDown(int keyCode, char character);



	~ComboBox();
};

