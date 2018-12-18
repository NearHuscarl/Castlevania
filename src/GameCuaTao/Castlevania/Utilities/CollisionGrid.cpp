#include "Direct2DGame/Base/Rect.h"
#include "CollisionGrid.h"

//CollisionGrid::CollisionGrid(int columns, int rows, int cellWidth, int cellHeight)
//{
//	for (auto row = 0; row < rows; row++)
//	{
//		cells.push_back(std::vector<CollisionCell>{}); // Add new row
//
//		for (auto column = 0; column < columns; column++)
//		{
//			auto rect = Rect{
//				cellWidth * column,
//				cellHeight * row,
//				cellWidth,
//				cellHeight,
//			};
//
//			cells[row].push_back(cells{});
//		}
//	}
//}
//
//void CollisionGrid::Put(IColliable &object)
//{
//}
