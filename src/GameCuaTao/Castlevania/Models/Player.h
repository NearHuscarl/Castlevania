#pragma once

#include "Simon.h"
#include "IControllable.h"

namespace Castlevania
{
	class Player : public Simon, public IControllable
	{
		void Update(float deltaTime);
		void UpdateInput() override;
	};
}