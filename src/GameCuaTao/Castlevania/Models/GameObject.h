#pragma once

#include "Direct2DGame/Base/Vector.h"

namespace Castlevania
{
	class GameObject
	{
		void SetState(int state);
		int GetState();

	private:
		Vector position;
		Vector velocity;
		int state;
	};
}