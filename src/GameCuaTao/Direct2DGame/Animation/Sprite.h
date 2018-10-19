#pragma once

#include <string>
#include "../Base/BoundingBox.h"
#include "../Base/Vector.h"
#include "../Graphics/Texture.h"
#include "../Graphics/SpriteEffects.h"
#include "../Device.h"

class Sprite
{
public:
	Sprite();
	Sprite(std::string spriteID, BoundingBox boundingBox);
	void Draw(ISpriteBatch_ spriteBatch, Texture texture, Vector position, SpriteEffects effects);

private:
	std::string id;				// Sprite ID in the sprite database
	BoundingBox boundingBox;
};