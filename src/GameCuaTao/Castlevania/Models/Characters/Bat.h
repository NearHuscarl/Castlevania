#pragma once

#include "../AnimatedObject.h"

namespace Castlevania
{
	class Bat : public AnimatedObject
	{
	public:
		Bat();
		void LoadContent(ContentManager &content) override;
	};
}