#ifndef __ROW__
#define __ROW__
#include <vector>

class Slot;

class Row
{
	std::vector<Slot> slots;
	int id;
	public:
	int insertPiece(int val);// returns the new length of vector which is the position of the new piece in the vector or -1 if fails
	int getVal(int index);
	int getId();
	int getSize();
	Row(int id);
};

#endif
