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
	tileSet = std::make_unique<TileSet>(texture, tileWidth, tileHeight, rows, columns);
}

void TiledMap::CreateMapObjects(TiledMapObjects objects)
{
	this->objects = objects;
}

TiledMapObjects TiledMap::GetMapObjects()
{
	return objects;
}

void TiledMap::Draw(SpriteExtensions spriteBatch)
{
	auto camRect = spriteBatch.GetGraphicsDevice().GetViewport().Bounds();

	auto startRow = (int)camRect.left / tileWidth;
	auto endRow = (int)camRect.right / tileWidth + 1;
	auto startColumn = (int)camRect.top / tileHeight;
	auto endColumn = (int)camRect.bottom / tileHeight + 1;

	startRow = MathHelper::Clamp(startRow, 0, rows - 1);
	endRow = MathHelper::Clamp(endRow, 0, rows - 1);
	startColumn = MathHelper::Clamp(startColumn, 0, columns - 1);
	endColumn = MathHelper::Clamp(endColumn, 0, columns - 1);

	for (auto row = startRow; row < endRow; row++)
	{
		for (auto column = startColumn; column < endColumn; column++)
		{
			auto tile = tileSet->GetTile(row, column);
			auto rect = tile.GetTextureRegion().GetFrameRectangle();
			auto position = Vector2{ (float)rect.X(), (float)rect.Y() };

			spriteBatch.Draw(tile, position);
		}
	}
}
