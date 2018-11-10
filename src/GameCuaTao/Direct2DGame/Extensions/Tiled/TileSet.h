#pragma once

#include <map>
#include "../Sprites/Sprite.h"

using Tile = Sprite;
using Tiles = std::map<std::pair<int, int>, Tile>; // map[(row, column)] : Tile

class TileSet
{
public:
	TileSet(std::shared_ptr<Texture> texture, int tileWidth, int tileHeight, int rows, int columns);

	Tile &GetTile(int row, int column);

private:
	std::shared_ptr<Texture> texture;
	
	int tileWidth;
	int tileHeight;

	Tiles tiles;
};