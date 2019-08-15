#include "Player.h"
#include <string>


Player::Player(char name[]):isMyTurn(false)
{
	strcpy(this->name,name);
}

void Player::setName(char name[])
{
	strcpy(this->name,name);
}
char* Player::getName()
{
	return name;
}
void Player::setCount(int count)
{
	this->count=count;
}