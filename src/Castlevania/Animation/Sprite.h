#pragma once

#include <string>
#include "../Base/BoundingBox.h"
#include "../Base/Graphics.h"

class Sprite
{
public:
	static void Initialize(Graphics *graphics);
	
	Sprite(std::string id, BoundingBox boundingBox, GTexturePtr texture);
	void Draw(float x, float y);

private:
	std::string id;				// Sprite ID in the sprite database
	BoundingBox boundingBox;
	GTexturePtr texture;
	static Graphics *graphics;
};