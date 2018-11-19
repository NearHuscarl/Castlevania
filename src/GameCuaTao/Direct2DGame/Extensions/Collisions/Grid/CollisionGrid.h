#pragma once

#include <list>
#include <map>
#include "../IColliable.h"
#include "CollisionGridCell.h"

using Cells = std::map<std::pair<int, int>, CollisionGridCell>;

class CollisionGrid
{
public:
	void Put(IColliable &object);

private:
	int cellWidth;
	int cellHeight;

	Cells cells;
};