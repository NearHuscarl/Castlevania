#pragma once

namespace Castlevania
{
	using CollisionUnit = std::list<std::unique_ptr<GameObject>>::iterator;

	struct CollisionGridData
	{
		bool moveToNextCell = false;
		int oldCellCol;
		int oldCellRow;
		int newCellCol;
		int newCellRow;
		CollisionUnit unit;
	};
}