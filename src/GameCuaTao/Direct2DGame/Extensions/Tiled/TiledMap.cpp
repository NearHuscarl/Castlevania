#include "TiledMap.h"
#include "../../MathHelper.h"

TiledMap::TiledMap(std::string name, int width, int height, int tileWidth, int tileHeight, Color backgroundColor)
{
	this->name = name;
	this->width = width;
	this->height = height;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->backgroundColor = backgroundColor;
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

int TiledMap::GetWidthInPixels()
{
	return width * tileWidth;
}

int TiledMap::GetHeightInPixels()
{
	return height * tileHeight;
}

void TiledMap::CreateTileSet(std::shared_ptr<Texture> texture)
{
	tileSet = std::make_unique<TileSet>(texture, tileWidth, tileHeight, columns, rows);
}

void TiledMap::CreateMapObjects(TiledMapObjectGroups objects)
{
	this->objects = objects;
}

TiledMapObjectGroups TiledMap::GetMapObjects()
{
	return objects;
}

void TiledMap::Draw(SpriteExtensions &spriteBatch)
{
	auto camRect = spriteBatch.GetGraphicsDevice().GetViewport().Bounds();

	auto startRow = (int)camRect.top / tileHeight;
	auto endRow = (int)camRect.bottom / tileHeight;
	auto startColumn = (int)camRect.left / tileWidth;
	auto endColumn = (int)camRect.right / tileWidth;

	startRow = MathHelper::Clamp(startRow, 0, rows - 1);
	endRow = MathHelper::Clamp(endRow, 0, rows - 1);
	startColumn = MathHelper::Clamp(startColumn, 0, columns - 1);
	endColumn = MathHelper::Clamp(endColumn, 0, columns - 1);

	for (auto row = startRow; row <= endRow; row++)
	{
		for (auto column = startColumn; column <= endColumn; column++)
		{
			auto tile = tileSet->GetTile(row, column);
			auto rect = tile.GetTextureRegion().GetFrameRectangle();
			auto tilePosition = position + Vector2{ (float)rect.X(), (float)rect.Y() };

			spriteBatch.Draw(tile, tilePosition);
		}
	}
}