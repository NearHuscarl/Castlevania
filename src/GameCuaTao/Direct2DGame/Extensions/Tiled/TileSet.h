#pragma once

#include <vector>
#include "../Sprites/Sprite.h"

using Tile = Sprite;
using Tiles = std::vector<std::vector<Tile>>; // map[(row, column)] : Tile

class TileSet
{
public:
	TileSet(std::shared_ptr<Texture> texture, int tileWidth, int tileHeight, int columns, int rows);

	Tile &GetTile(int row, int column);

private:
	std::shared_ptr<Texture> texture;
	
	int tileWidth;
	int tileHeight;

	Tiles tiles;
};