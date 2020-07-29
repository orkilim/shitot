#include <iostream>
#include <vector>
#include "../Backend/Graphics.h"
#include "../Controllers/Label.h"
#include "../Controllers/Panel.h"
#include "../Backend/Border/Border.h"
#include "../Backend/EventEngine.h"
#include "../Controllers/Button.h"
#include "../Controllers/NumericBox.h"
#include "../Controllers/MessageBox.h"
#include "../Controllers/CheckList.h"
#include "../Controllers/TextBox.h"
#include "../Controllers/RadioBox.h"

using namespace std;

int main(int argc, char **argv)
{

Panel MainPanel(0, 0, 100, 100, new Double, Color::White, Color::Blue);
Panel SecPanel(6, 16, 20, 9, new Single, Color::Black, Color::Cyan);

Label Title("Welcome to our SE Methods project");
	Title.setLeft(35); 
	Label lcheckList("Check List:");
	lcheckList.setLeft(11);
	lcheckList.setTop(2);
	vector<string> check_list_options;
	check_list_options.push_back(" 1)     Option     ");
	check_list_options.push_back(" 2)     Option     ");
	check_list_options.push_back(" 3)     Option     ");
	check_list_options.push_back(" 4)     Option     ");
	CheckList ckList(6, 4, check_list_options);
	ckList.AddSelectedItem(1);
	ckList.AddSelectedItem(0);
	ckList.RemoveSelectedItem(1);
	ckList.RemoveSelectedItem(0);
	ckList.RemoveSelectedItem(1);

	Label lcombobox("Combobox:");
	lcombobox.setLeft(45);
	lcombobox.setTop(2);
}