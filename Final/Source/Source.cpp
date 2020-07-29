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


	Label lradioList("RadioBox:");
	lradioList.setLeft(79);
	lradioList.setTop(2);
	vector<string> radio_list_options;
	radio_list_options.push_back(" (1)     Option     ");
	radio_list_options.push_back(" (2)     Option     ");
	radio_list_options.push_back(" (3)     Option     ");
	radio_list_options.push_back(" (4)     Option     ");
	RadioBox rdList(74, 4, radio_list_options);
	rdList.SelectedItem(2);

	Label lpanel("Secondary Panel!");
	lpanel.setLeft(1);
	lpanel.setTop(2);


	MassageBox msg("Click To Close Me!");
	msg.SetVisability(true);
	msg.setLeft(34);
	msg.setTop(18);

	Label lNumeric("Numeric Box");
	NumericBox numeric(-9, 9, 82, 20);
	lNumeric.setLeft(79);
	lNumeric.setTop(17);

	Label ltextBox("TextBox:");
	ltextBox.setLeft(47);
	ltextBox.setTop(24);
	TextBox Text(30,27,36,"mmmmmmmmmmmmmmmm");

	MainPanel.addToPanel(&Title);
	MainPanel.addToPanel(&lcheckList);
	MainPanel.addToPanel(&ckList);
	MainPanel.addToPanel(&lcombobox);
	MainPanel.addToPanel(&lradioList);
	MainPanel.addToPanel(&rdList);
	SecPanel.addToPanel(&lpanel);
	MainPanel.addToPanel(&SecPanel);
	MainPanel.addToPanel(&msg);
	MainPanel.addToPanel(&lNumeric);
	MainPanel.addToPanel(&numeric);
	MainPanel.addToPanel(&ltextBox);
	MainPanel.addToPanel(&Text);
	
	EventEngine e;
	e.run(MainPanel);

}