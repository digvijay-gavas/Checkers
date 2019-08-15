#include "Menu.h"
#include "BoardGUI.h"
#include <conio.h>
#include<iostream>
using namespace std;
Menu::Menu()
{
	screen=GAME_SCREEN;
	selected();
}
void Menu::moveCursor(int dir)
{

}
void Menu::selected()
{
	switch (screen)
	{
	case START_SCREEN:
		cout<<"welcome";
		break;
	case MENU_SCREEN:
		cout<<"start the game";
		break;
	case GAME_SCREEN:
		showGame();
		break;
	
	}
}


void Menu::showGame()
{
	BoardGUI b;
	getch();
	char c='4';
	while(1)
	{
		c=getch();
		switch (c)
		{
		case 72://up
			b.moveCursor(BoardGUI::UP);
			break;
		case 80://down
			b.moveCursor(BoardGUI::DOWN);
			break;
		case 77://right
			b.moveCursor(BoardGUI::RIGHT);
			break;
		case 75://left
			b.moveCursor(BoardGUI::LEFT);
			break;
		case 65:
			break;
		case 13:
			b.selected();
			break;
		case 27://escape
			//break;
			goto Exit;
			break;
		}
Exit:
		if(c==27)//esc
		break;
	}
}