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

void TiledMap::CreateTileSet(std::shared_ptr<Texture> texture)
{
	tileSet = std::make_unique<TileSet>(texture, tileWidth, tileHeight, rows, columns);
}

void TiledMap::CreateMapObjects(TiledMapObjects objects)
{
	this->objects = objects;
}

void TiledMap::Draw(SpriteExtensions spriteBatch, Viewport viewport)
{
	auto viewportRect = viewport.Bounds();

	auto startRow = (int)viewportRect.left / tileWidth;
	auto endRow = (int)viewportRect.right / tileWidth + 1;
	auto startColumn = (int)viewportRect.top / tileHeight;
	auto endColumn = (int)viewportRect.bottom / tileHeight + 1;

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
			auto worldPosition = Vector2{ (float)rect.X(), (float)rect.Y() };
			auto camPosition = viewport.Project(worldPosition);

			spriteBatch.Draw(tile, camPosition);
		}
	}
}
