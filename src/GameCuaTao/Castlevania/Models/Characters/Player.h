#pragma once

#include "Simon.h"
#include "../IControllable.h"

namespace Castlevania
{
	class Player : public Simon, public IControllable
	{
	public:
		Player();
		void Update(float deltaTime);
		void UpdateInput() override;
	};
}