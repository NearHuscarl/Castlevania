#include "TiledMap.h"
#include "../../MathHelper.h"

TiledMap::TiledMap(std::string name, int width, int height, int tileWidth, int tileHeight)
{
	this->name = name;
	this->width = width;
	this->height = height;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->position = Vector2::Zero();
}

Vector2 TiledMap::GetPosition()
{
	return position;
}

void TiledMap::SetPosition(Vector2 position)
{
	this->position = position;
}

int TiledMap::GetWidth()
{
	return width;
}

int TiledMap::GetHeight()
{
	return height;
}

int TiledMap::GetWidthInPixels()
{
	return width * tileWidth;
}

int TiledMap::GetHeightInPixels()
{
	return height * tileHeight;
}

void TiledMap::SetTileLayer(std::unique_ptr<TileSet> tileLayer)
{
	this->tileLayer = std::move(tileLayer);
}

void TiledMap::SetMapObjects(TiledMapObjectGroups objects)
{
	this->objects = objects;
}

TiledMapObjectGroups TiledMap::GetMapObjects()
{
	return objects;
}

void TiledMap::Draw(SpriteExtensions &spriteBatch)
{
	auto camBbox = spriteBatch.GetGraphicsDevice().GetViewport().Bounds();

	auto startRow = (int)camBbox.top / tileHeight;
	auto endRow = (int)camBbox.bottom / tileHeight;
	auto startColumn = (int)camBbox.left / tileWidth;
	auto endColumn = (int)camBbox.right / tileWidth;

	startRow = MathHelper::Clamp(startRow, 0, rows - 1);
	endRow = MathHelper::Clamp(endRow, 0, rows - 1);
	startColumn = MathHelper::Clamp(startColumn, 0, columns - 1);
	endColumn = MathHelper::Clamp(endColumn, 0, columns - 1);

	for (auto row = startRow; row <= endRow; row++)
	{
		for (auto column = startColumn; column <= endColumn; column++)
		{
			auto &tile = tileLayer->at(row).at(column);
			auto &sprite = tile.GetSprite();
			auto tileBbox = tile.GetBoundingBox();
			auto tilePosition = position + Vector2{ tileBbox.X(), tileBbox.Y() };

			spriteBatch.Draw(sprite, tilePosition);
		}
	}
}