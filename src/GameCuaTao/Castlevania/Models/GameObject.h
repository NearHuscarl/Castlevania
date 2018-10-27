#pragma once

#include "Direct2DGame/Base/Vector2.h"

namespace Castlevania
{
	class GameObject
	{
		void SetState(int state);
		int GetState();

	private:
		Vector2 position;
		Vector2 velocity;
		int state;
	};
}