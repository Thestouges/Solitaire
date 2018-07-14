#include <string>
using namespace std;

class card {
public:
	card();
	card(int, int);
	void setnumber(int);
	void setsuit(int);
	int getnumber();
	int getsuit();
	void setface(bool);
	bool getface();
private:
	int number;
	int suit;
	bool faceup;
};