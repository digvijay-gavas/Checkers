#include <iostream>
class Player
{
public:
	Player(){}
	Player(char[]);
	void setCount(int);
	void setName(char[]);
	/*std::string*/ char* getName();
	bool isMyTurn;
private:
	int count;
	char name[50];
};