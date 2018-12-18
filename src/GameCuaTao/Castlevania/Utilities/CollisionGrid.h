#pragma once

#include <vector>
#include <map>
//#include "../IColliable.h"
#include "CollisionCell.h"

using CollisionCells = std::vector<std::vector<CollisionCell>>;

class CollisionGrid
{
public:
	CollisionGrid(int columns, int rows, int cellWidth, int cellHeight);
	//void Put(IColliable &object);

private:
	int cellWidth;
	int cellHeight;

	CollisionCells cells;
};