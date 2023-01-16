#include "gameboard.h"
#include "row.h"
#include "slot.h"
#include <iostream>

bool Gameboard::isGameOver(int rowPos, int colPos)
{
	bool state = false;
	for(int i = -1; i < 2; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			if(i == 0 && j == 0)
				continue;
			state = state||(numInDir(i,j,rowPos,colPos,0) + numInDir(-1*i,-1*j,rowPos,colPos,0) >= 3);
			std::cout << (numInDir(i,j,rowPos,colPos,0) + numInDir(-1*i,-1*j,rowPos,colPos,0))<< endl;
		}
	}
	return state;
}

Gameboard::Gameboard(int rowsNum, int colsNum):maxRow(rowsNum)
{
	for(int i = 0; i < colsNum; ++i)
	{
		rows.push_back(Row(i));
	}
}

int Gameboard::numInDir(int dir1, int dir2, int a, int b, int count)
{
	//if the row to the left or righht doesn't exist then you can't go further
	if(int(rows.size()) <= a+dir1 || a+dir1 < 0)
		return count;
	//if the slot is empty getVal will return -1 so same State will never be true
	bool sameState = (curPlayer == rows[a+dir1].getVal(b+dir2));
	if(sameState && 3 == count)
		return 4;
	else if(!sameState)
		return count;
	else
		return numInDir(dir1,dir2,a+dir1,b+dir2,count+1);
}

int Gameboard::makeMove(int row)
{
	curPlayer = (2 == curPlayer) ? 1 : 2;
	return rows[row].insertPiece(curPlayer);
}

int Gameboard::getCurPlayer(){
	return curPlayer;
}

void Gameboard::refresh(int rowsNum, int colsNum){
	maxRow = rowsNum;
	rows.clear();
	for(int i = 0; i < colsNum; ++i)
	{
		rows.push_back(Row(i));
	}
}