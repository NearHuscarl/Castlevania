#pragma once

#include "HolyWater.h"
#include "../Systems/Rendering/AnimationRenderingSystem.h"

namespace Castlevania
{
	class HolyWaterRenderingSystem : public AnimationRenderingSystem
	{
	public:
		HolyWaterRenderingSystem(HolyWater &parent, std::string animationPath);

	private:
		HolyWater &parent;
		void OnMoveStateChanged() override;
	};
}
