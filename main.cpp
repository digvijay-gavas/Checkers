#include <iostream>
#include <iomanip>
#include <conio.h>
#include "BoardGUI.h"
#include "Menu.h"


using namespace std;

void main()
{
	Menu m;
	
	char c='4';
	while(1)
	{
		c=getch();
		switch (c)
		{
		case 72://up
			m.moveCursor(BoardGUI::UP);
			break;
		case 80://down
			m.moveCursor(BoardGUI::DOWN);
			break;
		case 77://right
			m.moveCursor(BoardGUI::RIGHT);
			break;
		case 75://left
			m.moveCursor(BoardGUI::LEFT);
			break;
		case 65:
			break;
		case 13:
			m.selected();
			//m.selected();
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



	