#pragma once

#include <functional>
#include <vector>
#include <map>
//#include "../IColliable.h"
#include "CollisionCell.h"
#include "CollisionObject.h"
#include "../Models/Factories/ObjectCollection.h"
#include "../Models/UpdateData.h"

namespace Castlevania
{
	using CollisionCells = std::vector<std::vector<std::unique_ptr<CollisionCell>>>;
	
	enum class CollisionObjectType
	{
		Block,
		Static,
		Entity,
	};

	class CollisionGrid
	{
	public:
		CollisionGrid(int columns, int rows, int cellWidth, int cellHeight);

		bool IsOutOfRange(int col, int row);
		int GetCellWidth();
		int GetCellHeight();
		CollisionCell &GetCellAtPosition(Vector2 objectPosition);
		CollisionCell &GetCellAtIndex(int col, int row);
		
		void GetCellsFromBoundingBox(RectF boundingBox, std::function<void (CollisionCell &cell, int col, int row)> callback);
		void GetAllCells(std::function<void(CollisionCell &cell)> callback);

		void PopulateObjects(ObjectCollection &objectCollection);
		void Add(std::unique_ptr<GameObject> object, CollisionObjectType type);
		void Move(GameObject &object, Vector2 distance);

		void Update(UpdateData &updateData);
		void UpdateCell(int col, int row, UpdateData &updateData);

		std::vector<GameObject*> GetCollisionObjects(int col, int row);
		void GetObjectsFromCell(std::vector<GameObject*> &collisionObjects, int col, int row);

	private:
		int width;
		int height;

		int cellWidth;
		int cellHeight;

		CollisionCells cells;
	};
}