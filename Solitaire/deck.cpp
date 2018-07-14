#include "deck.h"

deck::deck() {
}

void deck::createdeck() {
	for (int i = 1; i <= 13; i++) {
		for (int j = 1; j <= 4; j++) {
			card tempcard(i, j);
			carddeck.push_back(tempcard);
		}
	}
}

void deck::createdeck(vector<card> dec) {
	carddeck = dec;
}

void deck::addcard(card card) {
	carddeck.push_back(card);
}

void deck::shuffle() {
	srand(unsigned(time(0)));
	random_shuffle(carddeck.begin(), carddeck.end());
}

card deck::draw(int amount) {
	card drawn = carddeck[0];
	carddeck.erase(carddeck.begin());
	return drawn;
}

vector<card> deck::getdeck() {
	return carddeck;
}

int deck::decksize() {
	return carddeck.size();
}

card deck::getcard(int index) {
	return carddeck[index];
}

void deck::removecard(int index){
	carddeck.erase(carddeck.begin() + index);
}

void deck::destroydeck() {
	carddeck.clear();
}
