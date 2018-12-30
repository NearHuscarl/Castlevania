#include "Tile.h"

Tile::Tile(Sprite sprite, RectF boundingBox) : sprite{ sprite }
{
	this->boundingBox = boundingBox;
}

Sprite &Tile::GetSprite()
{
	return sprite;
}

RectF Tile::GetBoundingBox()
{
	return boundingBox;
}
