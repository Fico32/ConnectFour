#ifndef __GAMEBOARD__
#define __GAMEBOARD__
#include <vector>

using namespace std;

class Row;

class Gameboard
{
	int maxRow;
	int curPlayer;
	vector<Row> rows;
	int numInDir(int dir1, int dir2, int a, int b, int count);
	public:
	Gameboard(int rowsNum, int colsNum);
	int makeMove(int row);
	int getCurPlayer();
	bool isGameOver(int a, int b);
	void refresh(int rowsNum, int colsNum);
};

#endif
