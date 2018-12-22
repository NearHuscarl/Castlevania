#pragma once

#include <unordered_map>
#include <vector>
#include "TileSet.h"
#include "../Sprites/SpriteExtensions.h"
#include "../Sprites/IDrawable.h"

using TiledMapObjectProperties = std::unordered_map<std::string, std::string>;
using TiledMapObjects = std::vector<TiledMapObjectProperties>;
using TiledMapObjectGroups = std::unordered_map<std::string, TiledMapObjects>;

class TiledMap : public IDrawable
{
public:
	TiledMap(std::string name, int width, int height, int tileWidth, int tileHeight, Color backgroundColor);

	Vector2 GetPosition();
	void SetPosition(Vector2 position);

	int GetWidth();
	int GetHeight();

	int GetWidthInPixels();
	int GetHeightInPixels();

	void CreateTileSet(std::shared_ptr<Texture> texture);
	void CreateMapObjects(TiledMapObjectGroups objects);
	TiledMapObjectGroups GetMapObjects();

	void Draw(SpriteExtensions &spriteBatch) override;

private:
	std::string name;
	Vector2 position;

	int width;
	int height;

	int tileWidth;
	int tileHeight;

	std::unique_ptr<TileSet> tileSet;
	TiledMapObjectGroups objects;
	Color backgroundColor = Color::Black();

	int &columns = width; // height in tiles
	int &rows = height; // width in tiles
};