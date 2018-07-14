#include "solitaire.h"

solitaire::solitaire() {
}

void solitaire::start() {
	drawpile.createdeck();
	drawpile.shuffle();

	for (int i = 0; i < 4; i++) {
		stack<card> temp;
		finalpile.push_back(temp);
	}

	for (int i = 0; i < 7; i++) {
		vector<card> temp;
		for (int j = 0; j < i; j++) {
			card card = drawpile.draw(1);
			card.setface(false);
			temp.push_back(card);
		}
		temp.push_back(drawpile.draw(1));
		field.push_back(temp);
	}
	drawcard();
	displayboard();
	play();
}

void solitaire::displayboard() {
	cout << "Cards in deck:" << drawpile.decksize()<<"\t";
	if (drawpile.decksize() < 10) {
		cout << "\t";
	}
	for (int i = 1; i <= 4; i++) {
		cout << i << "\t";
	}
	cout << endl;

	cout << "Drawn card: ";
	if (discardpile.decksize() == 0) {
		cout << "Empty";
	}
	else {
		displaynumber(carddisplay.getnumber());
		displaysuit(carddisplay.getsuit());
		if (carddisplay.getsuit() == 1 || carddisplay.getsuit() == 3) {
			cout << "(R)";
		}
		else {
			cout << "(B)";
		}
	}

	fliptopfacedown();

	cout << "\t";
	for (int i = 0; i < 4; i++) {
		if (finalpile[i].empty()) {
			cout << "Empty\t";
		}
		else {
			displaynumber(finalpile[i].top().getnumber());
			displaysuit(finalpile[i].top().getsuit());
			cout << "\t";
		}
	}

	cout << "\n\n\t";
	char c = 'a';
	for (int i = 0; i < field.size(); i++) {
		cout << c << "\t";
		c++;
	}
	cout << "\n";
	int x = 0;
	while (field[0].size() > x
		||field[1].size() > x
		||field[2].size() > x
		||field[3].size() > x
		||field[4].size() > x
		||field[5].size() > x
		||field[6].size() > x
		) {
		cout << x << "\t";

		for (int i = 0; i < field.size(); i++) {
			if (field[i].size() == 0 && x == 0) {
				cout << "Empty\t";
			}
			else if (field[i].size() <= x) {
				cout << "\t";
			}
			else if (field[i].size() > x) {
				if (field[i][x].getface()) {
					displaynumber(field[i][x].getnumber());
					displaysuit(field[i][x].getsuit());
					if (field[i][x].getsuit() == 1 || field[i][x].getsuit() == 3) {
						cout << "(R)";
					}
					else {
						cout << "(B)";
					}
				}
				else {
					cout << "X";
				}
				cout << "\t";
			}
		}

		cout << "\n";
		x++;
	}
	maxlength = x;
	cout << "\n";
}
void solitaire::fliptopfacedown() {
	for (int i = 0; i < field.size(); i++) {
		if (!field[i][field[i].size() - 1].getface()) {
			field[i][field[i].size() - 1].setface(true);
		}
	}
}

void solitaire::clearscreen() {
	cout << string(20, '\n');
}

void solitaire::displaynumber(int num) {
	switch (num)
	{
	case 1:
		cout << "A";
		break;
	case 11:
		cout << "J";
		break;
	case 12:
		cout << "Q";
		break;
	case 13:
		cout << "K";
		break;
	default:
		cout << num;
		break;
	}
}

void solitaire::displaysuit(int suit) {
	switch (suit)
	{
	case 1:
		cout << "D";
		break;
	case 2:
		cout << "C";
		break;
	case 3:
		cout << "H";
		break;
	case 4:
		cout << "S";
		break;
	default:
		break;
	}
}

void solitaire::drawcard() {
	if (drawpile.decksize() == 0) {
		drawpile = discardpile;
		discardpile.destroydeck();
	}

	discardpile.addcard(drawpile.draw(1));
	carddisplay = discardpile.getcard(discardpile.decksize() - 1);
}

void solitaire::play() {
	string input;
	string location;
	while (1) {
		cout << "\"d\" to draw\n";
		cout << "To move cards\ninput row number and column number(ex: 4b) to move or\n1-4 to move to and pull from top pile or\n\"dp\" to move from draw pile: ";

		cin >> input;

		if (input == "d") {
			drawcard();
			clearscreen();
			displayboard();
			continue;
		}

		else if (input == "dp" && discardpile.decksize() > 0) {
			cout << "Enter destination (1-4 for top pile and a-g for bottom pile): ";
			while (1) {
				cin >> location;
				if (validdestination(location)) {
					break;
				}
				else {
					cout << "Invalid destination: ";
				}
			}
		}

		else if (validfieldpoint(input)) {
			cout << "Enter destination (1-4 for top pile and a-g for bottom pile): ";
			while (1) {
				cin >> location;

				if (validdestination(location)
					&& location.length() == 1
					&& ((location >= "1" && location <= "4") 
						|| (location >= "a" && location <= "g"))){
					break;
				}
				else {
					cout << "Invalid destination: ";
				}
			}
		}
		else {
			cout << "Invalid input\n";
			continue;
		}

		movecards(input, location);
		clearscreen();
		displayboard();
	}
}

bool solitaire::validfieldpoint(string test) {
	//test for movement of finalpile
	if (test.length() == 1) {
		if (!(test[0] >= '1' && test[0] <= '4'))
			return false;
		else
			return true;
	}
	if (!(test.length() >= 2 && test.length() <= 3))
		return false;
	//test last character in string for a-g
	else if (!(test[test.length() - 1] >= 'a' && test[test.length() - 1] <= char('a' + field.size() - 1))) {
		return false;
	}
	//test first character(number)
	else if (test.length() == 2) {
		if (!(test[0] >= '0' && test[0] <= '9')) {
			return false;
		}
		
		else if (field[test[test.length() - 1] - 97].size() <= test[0] - 48) {
			return false;
		}

		else if (!field[test[test.length() - 1]-97][test[0]-48].getface()) {
			return false;
		}
	}
	//test double digit numbers
	else if (test.length() == 3) {
		if (!(test[0] >= '0' && test[0] <= '9'
			|| test[1] >= '0' && test[1] <= '9')) {
			return false;
		}
		else if (field[test[test.length() - 1] - 97].size() <= stoi(test.substr(0, 2))) {
			return false;
		}
		else if (!field[stoi(test.substr(0, 2))][test[0]-48].getface()) {
			return false;
		}
	}

	return true;
}

bool solitaire::validdestination(string& loc) {
	if (loc.length() == 1) {
		if (loc[0] >= '1' && loc[0] <= '4') {
			return true;
		}
		else if (loc[0] >= 'a' && loc[0] <= 'g') {
			return true;
		}
	}
		
	return false;
}

void solitaire::movecards(string loc, string des) {
	//move from draw pile to...
	if (loc == "dp") {
		card temp = discardpile.getcard(discardpile.decksize() - 1);
		//..fieldpile
		if (des[0] >= 'a' && des[0] <= 'g') {
			if (isaltcolor(temp, field[des[0] - 97][field[des[0] - 97].size() - 1])
				&& temp.getnumber()+1 == field[des[0] - 97][field[des[0] - 97].size() - 1].getnumber()) {
				field[des[0] - 97].push_back(temp);
			}
		}
		//..finalpile
		else if (des[0] >= '1' && des[0] <= '4') {
			if (finalpile[(des[0] - 48) - 1].empty() == true
				&&temp.getnumber() == 1) {
				finalpile[(des[0] - 48) - 1].push(temp);
			}
			else if (finalpile[(des[0] - 48) - 1].top().getnumber() == temp.getnumber() - 1
				&& finalpile[(des[0] - 48) - 1].top().getsuit() == temp.getsuit()) {
				finalpile[(des[0] - 48) - 1].push(temp);
			}
		}

		discardpile.removecard(discardpile.decksize() - 1);
		if (discardpile.decksize() != 0)
			carddisplay = discardpile.getcard(discardpile.decksize() - 1);
	}
	//move from finalpile to field
	else if (loc.length() == 1
		&& !(des[0] >= '1' && des[0] <= '4')) {
		if (finalpile[(loc[0] - 48)-1].top().getnumber() - 1 == field[des[0] - 97][field[des[0] - 97].size() - 1].getnumber()
			&& isaltcolor(finalpile[(loc[0] - 48) - 1].top(), field[des[0] - 97][field[des[0] - 97].size() - 1])) {
			field[des[0] - 97].push_back(finalpile[(loc[0] - 48) - 1].top());
			finalpile[(loc[0] - 48) - 1].pop();
		}
	}
	//move from field to...
	else if(loc.length() >= 2 && loc.length() <= 3){
		int row = 0;
		int col = loc[loc.length() - 1] - 97;
		if (loc.length() == 2) {
			row = stoi(loc.substr(0, 1));
		}
		else if (loc.length() == 3) {
			row = stoi(loc.substr(0, 2));
		}
		//..finalpile
		if (des[0] >= '1' && des[0] <= '4') {
			if (finalpile[des[0] - 48].size() == 0) {
				if (field[col][row].getnumber() == 1) {
					finalpile[(des[0] - 48) - 1].push(field[col][row]);
					field[col].erase(field[col].begin() + row);
				}
			}
			else if (row == field[col].size() - 1){
				if (field[col][row].getnumber() == 1
					&& finalpile[(des[0] - 48) - 1].size() == 0) {
					finalpile[(des[0] - 48) - 1].push(field[col][row]);
					field[col].erase(field[col].begin() + row);
				}
				else if (field[col][field[col].size() - 1].getsuit() == finalpile[(des[0] - 48) - 1].top().getsuit()
					&& field[col][field[col].size() - 1].getnumber() - 1 == finalpile[(des[0] - 48) - 1].top().getnumber()) {
					finalpile[(des[0] - 48) - 1].push(field[col][row]);
					field[col].erase(field[col].begin() + row);
				}
				
			}
		}
		//..field
		else if (des[0] >= 'a' && des[0] <= 'g') {
			if (field[col][row].getnumber()+1 == field[des[0]-97][field[des[0] - 97].size()-1].getnumber()
				&& isaltcolor(field[col][row], field[des[0] - 97][field[des[0] - 97].size() - 1])
				&& col != des[0] - 97) {
				cout << row << " : " << field[col].size() << endl;
				for (int i = row; i < field[col].size();) {
					field[des[0] - 97].push_back(field[col][row]);
					field[col].erase(field[col].begin() + row);
				}
			}
			else if (field[des[0] - 97].size() == 0) {//empty column
				for (int i = row; i < field[col].size();) {
					field[des[0] - 97].push_back(field[col][row]);
					field[col].erase(field[col].begin() + row);
				}
			}
		}
	}
}

bool solitaire::isaltcolor(card x, card des) {
	if (x.getsuit() == 1 || x.getsuit() == 3) {
		if (des.getsuit() == 2 || des.getsuit() == 4) {
			return true;
		}
		return false;
	}
	else {
		if (des.getsuit() == 1 || des.getsuit() == 3) {
			return true;
		}
		return false;
	}
}