#include <map>
#include "Player.h"

#define N_OF_CELL 8
#define PYLAER_1  1
#define PYLAER_2  -1
#define PYLAER_1Q  2
#define PYLAER_2Q  -2
#define EMPTY  0

/*------------------------------------------------------
* This is Rule engine for Game
*
*
*------------------------------------------------------*/

class GameEngine
{
public:
	GameEngine();
	const int (&playGround)[N_OF_CELL][N_OF_CELL];       // reference of _playGround array to GUI purpose
	std::multimap<int, int> getPosibleMoves(int,int);    // give the psooible moves according to player postion and turn
	int isMovePossible(int,int,int,int);                 // tell weather move is possible or not
	int makeMove(int,int,int,int);                       // make the move is move is valid
	
private:
	Player player1,player2;
	int _playGround[N_OF_CELL][N_OF_CELL];
	int x,y;
};