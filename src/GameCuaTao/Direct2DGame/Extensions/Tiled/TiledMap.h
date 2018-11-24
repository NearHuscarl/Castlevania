#pragma once

#include <map>
#include <vector>
#include "TileSet.h"
#include "../Sprites/SpriteExtensions.h"
#include "../Sprites/IDrawable.h"

using TiledMapObjectProperties = std::map<std::string, std::string>;
using TiledMapObjects = std::vector<TiledMapObjectProperties>;

class TiledMap : public IDrawable
{
public:
	TiledMap(std::string name, int width, int height, int tileWidth, int tileHeight, Color backgroundColor);

	Vector2 GetPosition();
	void SetPosition(Vector2 position);

	int GetWidthInPixels();
	int GetHeightInPixels();

	void CreateTileSet(std::shared_ptr<Texture> texture);
	void CreateMapObjects(TiledMapObjects objects);
	TiledMapObjects GetMapObjects();

	void Draw(SpriteExtensions &spriteBatch) override;

private:
	std::string name;
	Vector2 position;

	int width;
	int height;

	int tileWidth;
	int tileHeight;

	std::unique_ptr<TileSet> tileSet;
	TiledMapObjects objects;
	Color backgroundColor = Color::Black();

	int &columns = width; // height in tiles
	int &rows = height; // width in tiles
};