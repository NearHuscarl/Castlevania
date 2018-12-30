#pragma once

#include <unordered_map>
#include <vector>
#include "Tile.h"
#include "../Sprites/SpriteExtensions.h"
#include "../Sprites/IDrawable.h"

using TileSet = std::vector<std::vector<Tile>>;
using TiledMapObjectProperties = std::unordered_map<std::string, std::string>;
using TiledMapObjects = std::vector<TiledMapObjectProperties>;
using TiledMapObjectGroups = std::unordered_map<std::string, TiledMapObjects>;

class TiledMap : public IDrawable
{
public:
	TiledMap(std::string name, int width, int height, int tileWidth, int tileHeight);

	Vector2 GetPosition();
	void SetPosition(Vector2 position);

	int GetWidth();
	int GetHeight();

	int GetWidthInPixels();
	int GetHeightInPixels();

	void SetTileLayer(std::unique_ptr<TileSet> tileLayer);
	void SetMapObjects(TiledMapObjectGroups objects);
	TiledMapObjectGroups GetMapObjects();

	void Draw(SpriteExtensions &spriteBatch) override;

private:
	std::string name;
	Vector2 position;

	int width;
	int height;

	int tileWidth;
	int tileHeight;

	std::unique_ptr<TileSet> tileLayer;
	TiledMapObjectGroups objects;

	int &columns = width; // height in tiles
	int &rows = height; // width in tiles
};