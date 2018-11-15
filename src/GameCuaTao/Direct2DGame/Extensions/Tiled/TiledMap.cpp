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
	auto endRow = (int)camRect.right / tileWidth;
	auto startColumn = (int)camRect.top / tileHeight;
	auto endColumn = (int)camRect.bottom / tileHeight;

	startRow = MathHelper::Clamp(startRow, 0, rows - 1);
	endRow = MathHelper::Clamp(endRow, 0, rows - 1);
	startColumn = MathHelper::Clamp(startColumn, 0, columns - 1);
	endColumn = MathHelper::Clamp(endColumn, 0, columns - 1);

	//auto &mapTex = tileSet->GetTile(0, 0).GetTextureRegion().GetTexture();
	//spriteBatch.Draw(mapTex, Vector2{ 0, 0 }, &Rect{ 0, 0, 1600, 400 }, Color::White(), 0, Vector2::One(), SpriteEffects::None);
	for (auto row = startRow; row <= endRow; row++)
	{
		for (auto column = startColumn; column <= endColumn; column++)
		{
			auto tile = tileSet->GetTile(row, column);
			auto rect = tile.GetTextureRegion().GetFrameRectangle();
			auto position = Vector2{ (float)rect.X(), (float)rect.Y() };

			spriteBatch.Draw(tile, position);
		}
	}
}