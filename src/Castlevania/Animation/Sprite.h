#pragma once

#include "../Utilities/DirectX.h"

class Sprite
{
public:
	Sprite(int id, int left, int top, int right, int bottom, GTexturePtr texture);

	void Draw(float x, float y);

private:
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	GTexturePtr texture;
};