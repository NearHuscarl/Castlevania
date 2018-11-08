#include "TiledMap.h"

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
