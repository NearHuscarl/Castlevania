#pragma once

#include <string>
#include "../Base/BoundingBox.h"
#include "../GraphicsDeviceManager.h"

class Sprite
{
public:
	Sprite(std::string spriteID, BoundingBox boundingBox, IDirect3DTexture9 *texture);
	void Draw(ID3DXSprite *spriteHandler, float x, float y);

private:
	std::string id;				// Sprite ID in the sprite database
	BoundingBox boundingBox;
	IDirect3DTexture9 *texture;
	static GraphicsDeviceManager *graphics;
};