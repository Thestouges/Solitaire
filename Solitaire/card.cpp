#include "card.h"

card::card() {

}

card::card(int num, int sui) {
	number = num;
	suit = sui;
	faceup = true;
}

void card::setnumber(int num) {
	number = num;
}
void card::setsuit(int sui) {
	suit = sui;
}

int card::getnumber() {
	return number;
}

int card::getsuit() {
	return suit;
}

void card::setface(bool face) {
	faceup = face;
}

bool card::getface() {
	return faceup;
}