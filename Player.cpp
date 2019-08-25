#include "Player.h"
#include <string>


Player::Player(char name[], int count):isMyTurn(false)
{
	this->count = count;
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
int Player::getCount()
{
	return this->count;
}

void Player::decreaseCount()
{
	 this->count--;
}