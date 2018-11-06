#pragma once

#include "../Base/Vector2.h"

struct Transform
{
	Vector2 position;
	float rotation;
	Vector2 scale = Vector2::One();
};