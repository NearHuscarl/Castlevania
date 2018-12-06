#pragma once

#include <memory>
#include "Direct2DGame/Extensions/Sprites/Sprite.h"

namespace Castlevania
{
	class DevTool
	{
	public:
		DevTool();

	private:
		std::unique_ptr<Sprite> sprite;
	};
}