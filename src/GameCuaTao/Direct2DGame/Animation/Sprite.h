#pragma once

#include <string>
#include "../Base/BoundingBox.h"
#include "../Base/Texture.h"
#include "../Base/Vector.h"
#include "../Device.h"

class Sprite
{
public:
	Sprite();
	Sprite(std::string spriteID, BoundingBox boundingBox);
	void Draw(ISpriteHandler_ spriteHandler, Texture texture, Vector position);

private:
	std::string id;				// Sprite ID in the sprite database
	BoundingBox boundingBox;
};