#include "deck.h"
#include <stack>
#include <iostream>
using namespace std;

class solitaire {
public:
	solitaire();
	void start();
	void displayboard();
	void clearscreen();
	void fliptopfacedown();
	void displaynumber(int);
	void displaysuit(int);
	void drawcard();
	void play();
	bool validfieldpoint(string);
	bool validdestination(string&);
	void movecards(string, string);
	bool isaltcolor(card, card);
private:
	int maxlength;
	deck drawpile;
	deck discardpile;
	card carddisplay;
	vector<stack<card>> finalpile;
	vector<vector<card>> field;
};
