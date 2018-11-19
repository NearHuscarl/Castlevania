#pragma once

#include "../Systems/ICollisionResponseSystem.h"
#include "Whip.h"

namespace Castlevania
{
	class WhipResponseSystem : public ICollisionResponseSystem
	{
	public:
		WhipResponseSystem(Whip &parent);

		void Update(ObjectCollection &objectCollection);

	private:
		Whip &parent;
	};
}