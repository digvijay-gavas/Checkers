#include <windows.h>
#include "BoardGUI.h"

#define CELL_WIDTH 6
#define CELL_HEIGTH 3

using namespace std;

BoardGUI::BoardGUI():cx(0),cy(0),cxm(0),cym(0),isCursorSelected(false),isMoveSelected(false)
{
	//Initialization---------------------------------------------------------------------------------------------------------
	symbols[0] = ' ';
	symbols[1] = 'o';
	symbols[2] = 'u';
	symbols[3] = 'O';
	symbols[4] = 'U';
	symbols[5] = '>';
	

	stdoutH = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//char name[50];
	//cout<<"Give player1 name"<<endl;
	//cin>>name;
	//game.player1.setName(name);
	//cout<<"Give player2 name"<<endl;
	//cin>>name;
	//game.player2.setName(name);
	//system("cls");

	// Initialization of board on console window----------------------------------------------------------------------------
	SetConsoleTextAttribute(stdoutH,0x000F);
	for(int j=0;    j< CELL_HEIGTH*N_OF_CELL+1;   j+=1)
	{	
		if(j%CELL_HEIGTH==0)
		{		
			for(int i=0;  i<CELL_WIDTH*N_OF_CELL+1;  i+=1)
			{
				if(i%CELL_WIDTH==0)
					cout<<'|';
				else
				cout<<'-';
			}
			cout<<endl;
		}
		else
		{
			for(int i=0;  i<CELL_WIDTH*N_OF_CELL+1;  i+=1)
			{
				

				if(i%CELL_WIDTH==0)
					cout<<'|';
				else
				{
					if((i/CELL_WIDTH+j/CELL_HEIGTH)%2==0)
					SetConsoleTextAttribute(stdoutH,0x000F);
					else
					SetConsoleTextAttribute(stdoutH,0x008F);
					cout<<' ';
					SetConsoleTextAttribute(stdoutH,0x008F);
				}
			}
			cout<<endl;
		}
	}
	SetConsoleTextAttribute(stdoutH,0x000F);
	updateBoard();

	// Writing instructions on board for User-------------------------------------------------------------------------------
	setConsoleCursor(N_OF_CELL*CELL_WIDTH+2,1);
	cout<<" ] Press Arrow Keys to Move Cursor";
	setConsoleCursor(N_OF_CELL*CELL_WIDTH+2,3);
	cout<<" ] Press Esc to exit";
	/*setConsoleCursor(N_OF_CELL*CELL_W+2,4);
	cout<<" ] Player1: "<<game.player1.getName();
	setConsoleCursor(N_OF_CELL*CELL_W+2,5);
	cout<<" ] Player2: "<<game.player2.getName();*/
	updateBoard();
	//-------------------------------------------------------------------------------------------------
}


void BoardGUI::updateBoard()
{
	SetConsoleTextAttribute(stdoutH,0x000F);
	for (int i=0;i<N_OF_CELL;i++)
	{
		for(int j=0;j<N_OF_CELL;j++)
		{
			
			setConsoleCursor(i*CELL_WIDTH + CELL_WIDTH/2-1,j*CELL_HEIGTH + CELL_HEIGTH/2);
			if(game.playGround[i][j]==PYLAER_1 )
				print_player(i,j,1);
			else if(game.playGround[i][j]==PYLAER_2 )
				print_player(i,j,2);
			else if(game.playGround[i][j]==PYLAER_1Q )
				print_player(i,j,3);
			else if(game.playGround[i][j]==PYLAER_2Q )
				print_player(i,j,4);
			else if(game.playGround[i][j]==EMPTY)
			{
					if((i+j)%2==0)
					SetConsoleTextAttribute(stdoutH,0x000F);
					else
					SetConsoleTextAttribute(stdoutH,0x008F);
				print_player(i,j,0);
				SetConsoleTextAttribute(stdoutH,0x000F);
			}
		}
		cout<<endl;
	}

	setConsoleCursor(N_OF_CELL * CELL_WIDTH + CELL_WIDTH, (N_OF_CELL - 1 ) * CELL_HEIGTH + CELL_HEIGTH-1);
	cout << (game.isPlayer1MyTurn() ? "-> " : "   ") << game.getPlayer1Name() << "  " << game.getPlayer1Count() << "  " << endl;
	setConsoleCursor(N_OF_CELL * CELL_WIDTH + CELL_WIDTH, (N_OF_CELL - 1) * CELL_HEIGTH + CELL_HEIGTH);
	cout << (game.isPlayer2MyTurn() ? "-> " : "   ") << game.getPlayer2Name() << "  " << game.getPlayer2Count() << "  " << endl;
	
}
// selecting symbols for player 1 and 2
void BoardGUI::print_player(int i,int j,int sym)
{
	setConsoleCursor(i*CELL_WIDTH + CELL_WIDTH/2,j*CELL_HEIGTH + CELL_HEIGTH/2);
	cout<<symbols[sym];
}
// Cursor Related Functions--------------------------------------------------------------------------------------------------
void BoardGUI::setConsoleCursor(int x,int y)
{
	cursr.X=x;
	cursr.Y=y;
	SetConsoleCursorPosition(stdoutH,cursr);
}
void BoardGUI::setCursor(char a,int x,int y)
{
	setConsoleCursor((x)*CELL_WIDTH+1,(y)*CELL_HEIGTH);
	for(int i=0;i<CELL_WIDTH-1;i++)
	cout<<a;
	setConsoleCursor((x)*CELL_WIDTH+1,(y+1)*CELL_HEIGTH);
	for(int i=0;i<CELL_WIDTH-1;i++)
	cout<<a;
}
void BoardGUI::clearCursor()
{
	setConsoleCursor((cx)*CELL_WIDTH+1,(cy)*CELL_HEIGTH);
	for(int i=0;i<CELL_WIDTH-1;i++)
	cout<<'-';
	setConsoleCursor((cx)*CELL_WIDTH+1,(cy+1)*CELL_HEIGTH);
	for(int i=0;i<CELL_WIDTH-1;i++)
	cout<<'-';
}
void BoardGUI::moveCursor(int dir)
{	
	if(isCursorSelected)
	{
		setCursor('-',cxm,cym);
		if(UP==dir  && cym-1!=-1)
			cym--;
		else if(DOWN==dir && cym+1!=N_OF_CELL)
			cym++;
		else if(LEFT==dir && cxm-1!=-1)
			cxm--;
		else if(RIGHT==dir && cxm+1!=N_OF_CELL)
			cxm++;
		setCursor('=',cxm,cym);
		setCursor('+',cx,cy);
	}
	else
	{
		moves=game.getPosibleMoves(cx,cy);
		for(multimap<int,int>::iterator ir=moves.begin();  ir!=moves.end();  ir++)
		{
			setConsoleCursor((ir->first)*CELL_WIDTH+CELL_WIDTH/2,(ir->second)*CELL_HEIGTH+CELL_HEIGTH/2);
			cout<<" ";
		}
		setCursor('-',cx,cy);
		if(UP==dir  && cy-1!=-1)
			cy--;
		else if(DOWN==dir && cy+1!=N_OF_CELL)
			cy++;
		else if(LEFT==dir && cx-1!=-1)
			cx--;
		else if(RIGHT==dir && cx+1!=N_OF_CELL)
			cx++;
		cxm=cx;
		cym=cy;
		setCursor('+',cx,cy);
		moves=game.getPosibleMoves(cx,cy);
		for(multimap<int,int>::iterator ir=moves.begin();  ir!=moves.end();  ir++)
		{
			setConsoleCursor((ir->first)*CELL_WIDTH+CELL_WIDTH/2,(ir->second)*CELL_HEIGTH+CELL_HEIGTH/2);
			cout<<symbols[5];
		}
	}
		
}

void BoardGUI::selected()
{
	if (cx==cxm && cy==cym )
	{ 
		isCursorSelected=!isCursorSelected;
		setCursor('=',cx,cy);

	}
	else if(0==game.makeMove(cx,cy,cxm,cym))
	{

		setCursor('-',cx,cy);
		isCursorSelected=!isCursorSelected;
		cx=cxm;cy=cym;
		setCursor('+',cx,cy);
		updateBoard();
	}
}
