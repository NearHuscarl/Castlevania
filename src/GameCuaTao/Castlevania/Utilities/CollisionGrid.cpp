#include "Direct2DGame/Base/Rect.h"
#include "Direct2DGame/MathHelper.h"
#include "Direct2DGame/Utilities/CppExtensions.h"
#include "CollisionGrid.h"

using namespace Castlevania;

CollisionGrid::CollisionGrid(int columns, int rows, int cellWidth, int cellHeight)
{
	this->width = columns;
	this->height = rows;
	this->cellWidth = cellWidth;
	this->cellHeight = cellHeight;
	
	for (auto column = 0; column < columns; column++)
	{
		cells.push_back(std::vector<std::unique_ptr<CollisionCell>>{}); // Add new column

		for (auto row = 0; row < rows; row++)
		{
			auto rect = RectF{
				(float)cellWidth * column,
				(float)cellHeight * row,
				(float)cellWidth,
				(float)cellHeight,
			};

			cells[column].push_back(std::make_unique<CollisionCell>(rect));
		}
	}
}

bool CollisionGrid::IsOutOfRange(int col, int row)
{
	return (col < 0 || col > width - 1 || row < 0 || row > height - 1);
}

int CollisionGrid::GetCellWidth()
{
	return cellWidth;
}

int CollisionGrid::GetCellHeight()
{
	return cellHeight;
}

CollisionCell &CollisionGrid::GetCellAtPosition(Vector2 position)
{
	auto cellCol = (int)(position.x / cellWidth);
	auto cellRow = (int)(position.y / cellHeight);

	if (IsOutOfRange(cellCol, cellRow))
		return CollisionCell::NullCell();

	return *cells.at(cellCol).at(cellRow);
}

CollisionCell &CollisionGrid::GetCellAtIndex(int col, int row)
{
	return *cells.at(col).at(row);
}

void CollisionGrid::GetCellsFromBoundingBox(RectF boundingBox,
	std::function<void(CollisionCell &cell, int col, int row)> callback)
{
	auto startRow = (int)(boundingBox.top / cellHeight);
	auto endRow = (int)(boundingBox.bottom / cellHeight);
	auto startColumn = (int)(boundingBox.left / cellWidth);
	auto endColumn = (int)(boundingBox.right / cellWidth);

	startRow = MathHelper::Clamp(startRow, 0, height - 1);
	endRow = MathHelper::Clamp(endRow, 0, height - 1);
	startColumn = MathHelper::Clamp(startColumn, 0, width - 1);
	endColumn = MathHelper::Clamp(endColumn, 0, width - 1);

	for (auto column = startColumn; column <= endColumn; column++)
	{
		for (auto row = startRow; row <= endRow; row++)
		{
			callback(*cells.at(column).at(row), column, row);
		}
	}
}

void CollisionGrid::GetAllCells(std::function<void(CollisionCell &cell)> callback)
{
	for (auto column = 0; column < width; column++)
	{
		for (auto row = 0; row < height; row++)
		{
			callback(*cells[column][row]);
		}
	}
}

void CollisionGrid::PopulateObjects(ObjectCollection &objectCollection)
{
	for (auto &object : objectCollection.blocks)
	{
		Add(std::move(object), CollisionObjectType::Block);
	}

	for (auto &object : objectCollection.staticObjects)
	{
		Add(std::move(object), CollisionObjectType::Static);
	}

	for (auto &object : objectCollection.entities)
	{
		Add(std::move(object), CollisionObjectType::Entity);
	}
}

void CollisionGrid::Add(std::unique_ptr<GameObject> object, CollisionObjectType type)
{
	object->Attach(this);

	auto bBox = object->GetBoundingBox();
	auto position = Vector2{ bBox.left, bBox.top };
	
	switch (type)
	{
		case CollisionObjectType::Block:
		{
			auto &cell = GetCellAtPosition(position);
			auto &existedObjects = cell.GetStaticObjects();
			auto existed = false;

			for (auto &existedObject : existedObjects)
			{
				if (existedObject->GetId() != ObjectId::Boundary)
					continue;

				if (existedObject->GetBoundingBox() == object->GetBoundingBox())
				{
					existed = true;
					break;
				}
			}

			if (!existed)
				cell.AddStaticObject(std::move(object));
			break;
		}

		case CollisionObjectType::Static:
			GetCellAtPosition(position).AddStaticObject(std::move(object));
			break;

		case CollisionObjectType::Entity:
			GetCellAtPosition(position).AddEntity(std::move(object));
			break;
	}
}

void CollisionGrid::Move(GameObject &object, Vector2 distance)
{
	auto oldPosition = object.GetPosition();
	auto oldBoundingBox = object.GetBoundingBox();
	auto newPosition = oldPosition + distance;
	
	object.SetRawPosition(newPosition);
	
	auto newBoundingBox = object.GetBoundingBox();
	
	auto oldCellCol = (int)(oldBoundingBox.X() / cellWidth);
	auto oldCellRow = (int)(oldBoundingBox.Y() / cellHeight);
									
	auto newCellCol = (int)(newBoundingBox.X() / cellWidth);
	auto newCellRow = (int)(newBoundingBox.Y() / cellHeight);

	if (oldCellCol == newCellCol && oldCellRow == newCellRow)
		return;

	if (IsOutOfRange(newCellCol, newCellRow))
	{
		object.Destroy();
		return;
	}

	auto collisionGridData = CollisionGridData{
		true,
		oldCellCol,
		oldCellRow,
		newCellCol,
		newCellRow,
		object.GetCollisionGridData().unit,
	};

	object.SetCollisionGridData(collisionGridData);
}

void CollisionGrid::Update(UpdateData &updateData)
{
	GetCellsFromBoundingBox(updateData.viewport, [&](CollisionCell &cell, int col, int row)
	{
		if (cell.GetEntites().empty())
			return;

		UpdateCell(col, row, updateData);
	});
}

void CollisionGrid::UpdateCell(int col, int row, UpdateData &updateData)
{
	auto &cell = *cells[col][row];
	auto &entities = cell.GetEntites();
	auto collisionObjects = GetCollisionObjects(col, row);

	updateData.collisionObjects = &collisionObjects;

	// Only update existing objects. Any new objects will have to wait until next turn
	// That way, a newly spawned object wont get a chance to act during the same frame
	// that it was spawned, before the player has even had a chance to see it
	auto sizeThisTurn = entities.size();

	for (auto it = entities.begin(); it != std::next(entities.begin(), sizeThisTurn); std::advance(it, 1))
	{
		auto object = (*it).get();

		object->Update(updateData);
	}

	// Defer modifying the list until now. Post processing code walk the list
	// again to remove dead objects or move objects to another cell
	for (auto it = entities.end(); it != entities.begin(); )
	{
		std::advance(it, -1);
		auto object = (*it).get();

		if (object->GetState() == ObjectState::DEAD)
		{
			it = entities.erase(it);
			continue;
		}

		auto data = object->GetCollisionGridData();

		if (data.moveToNextCell)
		{
			auto &oldCell = *cells[data.oldCellCol][data.oldCellRow];
			auto &newCell = *cells[data.newCellCol][data.newCellRow];
			
			it = Transfer(oldCell.GetEntites(), newCell.GetEntites(), data.unit);
			data.moveToNextCell = false;
			object->SetCollisionGridData(data);
		}
	}
}

std::vector<GameObject*> CollisionGrid::GetCollisionObjects(int col, int row)
{
	auto collisionObjects = std::vector<GameObject*>{};

	if (col > 0 && row > 0)	                 GetObjectsFromCell(collisionObjects, col - 1, row - 1);
	if (col > 0)				                 GetObjectsFromCell(collisionObjects, col - 1, row    );
	if (col > 0 && row < height - 1)         GetObjectsFromCell(collisionObjects, col - 1, row + 1);
	if (row > 0)                             GetObjectsFromCell(collisionObjects, col,     row - 1);
	                                         GetObjectsFromCell(collisionObjects, col,     row    );
	if (row < height - 1)                    GetObjectsFromCell(collisionObjects, col,     row + 1);
	if (col < width - 1 && row > 0)          GetObjectsFromCell(collisionObjects, col + 1, row - 1);
	if (col < width - 1)                     GetObjectsFromCell(collisionObjects, col + 1, row    );
	if (col < width - 1 && row < height - 1) GetObjectsFromCell(collisionObjects, col + 1, row + 1);

	return collisionObjects;
}

void CollisionGrid::GetObjectsFromCell(std::vector<GameObject*> &collisionObjects, int col, int row)
{
	if (IsOutOfRange(col, row))
		return;

	auto &cellObjects = cells.at(col).at(row)->GetObjects();
	auto &entities = cellObjects.entities;
	auto &staticObjects = cellObjects.staticObjects;

	for (auto &entity : entities)
		collisionObjects.push_back(entity.get());

	for (auto &staticObject : staticObjects)
		collisionObjects.push_back(staticObject.get());
}
