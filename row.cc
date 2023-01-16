#include "row.h"
#include "slot.h"

int Row::insertPiece(int val)
{
	slots.push_back(Slot(val));
	return slots.size()-1;
}

int Row::getVal(int index)
{
	if(index >= slots.size() || index < 0)
		return -1;
	return slots[index].getValue();
}

int Row::getId()
{
	return id;
}

int Row::getSize()
{
	return slots.size();
}

Row::Row(int id): id(id){}