#include <iostream>
class Player
{
public:
	Player(char[], int count);
	int getCount();
	void decreaseCount();
	void setName(char[]);
	/*std::string*/ char* getName();
	bool isMyTurn;
private:
	int count;
	char name[50];
};