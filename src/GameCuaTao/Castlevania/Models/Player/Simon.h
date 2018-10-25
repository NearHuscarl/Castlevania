#pragma once

#include "../GameObject.h"
#include "../IControllable.h"

namespace Castlevania
{
	class Simon : public GameObject, IControllable
	{
		void UpdateInput() override;
	};
}