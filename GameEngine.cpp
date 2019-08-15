using namespace std; 
#include "GameEngine.h"

GameEngine::GameEngine():playGround(_playGround)
{
	// Setting player turns
	player1.isMyTurn=true;
	player2.isMyTurn=false;
	// Positioning players in playGround array-------------------------------------------------------------
	for (int i=0;i<N_OF_CELL;i++)
	{
		for(int j=0;j<N_OF_CELL;j++)
		{
			_playGround[j][i]=EMPTY;
		}
	}
	for (int i=0;i<3;i++)
	{
		for(int j=i%2;j<N_OF_CELL;j+=2)
		{
			_playGround[j][i] =PYLAER_1;
		}
	}
	for(int i=N_OF_CELL-3;i<N_OF_CELL;i++)
	{
		for(int j=i%2;j<N_OF_CELL;j+=2)
		{
			_playGround[j][i]=PYLAER_2;
		}
	}

}

int GameEngine::isMovePossible(int x,int y,int x1,int y1)
{
	if(EMPTY==_playGround[x][y])
		return 0;
	int i=x1-x,j=y1-y,k=abs(x-x1);
	if(abs(x-x1)!=abs(y-y1))
		return -1;
	// Filter to for empty cell___________________________________________________________________________
	if( EMPTY==_playGround[x+i][y+j] /*isEmpty Filter*/
		&& x+i>=0 && x+i<N_OF_CELL  &&  y+j>=0 && y+j<N_OF_CELL /*isInBound Filter*/
		&&  ( PYLAER_2Q==_playGround[x][y]  || PYLAER_1Q==_playGround[x][y]  ||  j*_playGround[x][y]>0)  /*isQueen and isForwardMove Filter*/)
	{
		// Filter for immediate neighbour_________________________________________________________________  
		if(1==k) 
		/*(k=1 for immediate neighbour*/
		{
			return 1;
		}
		// Filter for second neighbour____________________________________________________________________ 
		else if(2==k  &&  EMPTY!=_playGround[(x+x+i)/2][(y+y+j)/2] &&    _playGround[(x+x+i)/2][(y+y+j)/2]/abs(_playGround[(x+x+i)/2][(y+y+j)/2])==-_playGround[x][y]/abs(_playGround[x][y])) 
		/*(k=2 for second neighbour  && player is diffrent than at (x,y))*/
		{
			return 2;
		}
					
	}

	return -1;
}
std::multimap<int, int> GameEngine::getPosibleMoves(int x,int y)
{
	std::multimap<int, int> moves;
	if( ((PYLAER_1==_playGround[x][y] || PYLAER_1Q==_playGround[x][y]) + player1.isMyTurn)%2)	
		return moves;
	else if( ((PYLAER_2==_playGround[x][y] || PYLAER_2Q==_playGround[x][y]) + player2.isMyTurn)%2)	
		return moves;

	for(int k=1;k<=2;k++)
		for(int i=-k;i<=k;i+=2*k)
			for(int j=-k;j<=k;j+=2*k)
			{
				if(EMPTY==_playGround[x][y])
					return moves;
				// Filter to for empty cell___________________________________________________________________________
				if( EMPTY==_playGround[x+i][y+j]/*isEmpty Filter*/
					&& x+i>=0 && x+i<N_OF_CELL  &&  y+j>=0 && y+j<N_OF_CELL/*isInBound Filter*/
					&&  ( PYLAER_2Q==_playGround[x][y]  || PYLAER_1Q==_playGround[x][y]  ||  j*_playGround[x][y]>0)  /*isQueen and isForwardMove Filter*/)
				{
					// Filter for immediate neighbour_________________________________________________________________  
					if(1==k) 
					/*(k=1 for immediate neighbour*/
					{
						moves.insert(pair<int,int>(x+i,y+j));
					}
					// Filter for second neighbour____________________________________________________________________ 
					else if(2==k  &&  EMPTY!=_playGround[(x+x+i)/2][(y+y+j)/2] &&    _playGround[(x+x+i)/2][(y+y+j)/2]/abs(_playGround[(x+x+i)/2][(y+y+j)/2])==-_playGround[x][y]/abs(_playGround[x][y])) 
					/*(k=2 for second neighbour  && player is diffrent than at (x,y))*/
					{
						moves.insert(pair<int,int>(x+i,y+j));
					}
					
				}
			}
	return moves;
}



int GameEngine::makeMove(int cx,int cy,int cxm,int cym)
{
	if( (PYLAER_1==_playGround[cx][cy] || PYLAER_1Q==_playGround[cx][cy]) && player1.isMyTurn)
	{
		if(1==isMovePossible(cx,cy,cxm,cym))
		{
			_playGround[cxm][cym] = _playGround[cx][cy];
			_playGround[cx][cy] =EMPTY ;
			player1.isMyTurn=false;
			player2.isMyTurn=true;
			if(cxm>=0 && cxm<N_OF_CELL && cym==N_OF_CELL-1)
				_playGround[cxm][cym]=PYLAER_1Q;
			return 0;
		}
		else if(2==isMovePossible(cx,cy,cxm,cym))
		{
			_playGround[cxm][cym] = _playGround[cx][cy];
			_playGround[(cx+cxm)/2][(cy+cym)/2]=EMPTY;
			_playGround[cx][cy] =EMPTY ;
			player1.isMyTurn=false;
			player2.isMyTurn=true;
			if(cxm>=0 && cxm<N_OF_CELL && cym==N_OF_CELL-1)
				_playGround[cxm][cym]=PYLAER_1Q;
			return 0;
		}
		return -1;
		
	}
	else if( (PYLAER_2==_playGround[cx][cy] || PYLAER_2Q==_playGround[cx][cy]) && player2.isMyTurn)
	{
		if(1==isMovePossible(cx,cy,cxm,cym))
		{
			_playGround[cxm][cym] = _playGround[cx][cy];
			_playGround[cx][cy] =EMPTY ;
			player2.isMyTurn=false;
			player1.isMyTurn=true;
			if(cxm>=0 && cxm<N_OF_CELL && cym==0)
				_playGround[cxm][cym]=PYLAER_2Q;
			return 0;
		}
		else if(2==isMovePossible(cx,cy,cxm,cym))
		{
			_playGround[cxm][cym] = _playGround[cx][cy];
			_playGround[(cx+cxm)/2][(cy+cym)/2]=EMPTY;
			_playGround[cx][cy] =EMPTY ;
			player2.isMyTurn=false;
			player1.isMyTurn=true;
			if(cxm>=0 && cxm<N_OF_CELL && cym==0)
				_playGround[cxm][cym]=PYLAER_2Q;
			return 0;
		}
		return -1;
		
	}
	
}