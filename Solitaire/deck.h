#include "card.h"
#include <vector>
#include <algorithm>
#include <time.h>
#include <cstdlib>
using namespace std;

class deck {
public:
	deck();
	void createdeck();
	void createdeck(vector<card>);
	void shuffle();
	card draw(int);
	void addcard(card);
	vector<card> getdeck();
	int decksize();
	card getcard(int);
	void removecard(int);
	void destroydeck();
private:
	vector<card> carddeck;
};
