#pragma once

#include <map>
#include <vector>
#include "TileSet.h"
#include "../Sprites/SpriteExtensions.h"

using TiledMapObjectProperties = std::map<std::string, std::string>;
using TiledMapObjects = std::vector<TiledMapObjectProperties>;

class TiledMap
{
public:
	TiledMap(std::string name, int width, int height, int tileWidth, int tileHeight, Color backgroundColor);

	int GetWidthInPixels();
	int GetHeightInPixels();

	void CreateTileSet(std::shared_ptr<Texture> texture);
	void CreateMapObjects(TiledMapObjects objects);
	TiledMapObjects GetMapObjects();

	void Draw(SpriteExtensions spriteBatch);

private:
	std::string name;

	int width;
	int height;

	int tileWidth;
	int tileHeight;

	std::unique_ptr<TileSet> tileSet;
	TiledMapObjects objects;
	Color backgroundColor = Color::Black();

	int &rows = width; // width in tiles
	int &columns = height; // height in tiles
};