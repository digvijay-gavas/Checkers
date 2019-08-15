#include <windows.h>
#include "GameEngine.h"

/*------------------------------------------------------
* This class do dispaly checkes board on console
*
*
*------------------------------------------------------*/


class BoardGUI
{
public:
	BoardGUI();
	//BoardGUI(int,int);
	void updateBoard();
	void moveCursor(int dir);
	void selected();  // when piece is selected 
	
	static enum {UP,DOWN,LEFT,RIGHT};
private:
	//char C[68][43];
	void setCursor(char,int,int);
	void setConsoleCursor(int,int);
	void clearCursor();
	void print_player(int,int,int);
	//void makeMove();
	bool isCursorSelected,isMoveSelected ;
	int cx,cy,cxm,cym;
	std::multimap<int,int> moves;
	GameEngine game;
	HANDLE stdoutH;
	COORD cursr;
	char symbols[10];
};