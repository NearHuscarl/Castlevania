#pragma once

#include "Door.h"
#include "../Systems/Rendering/AnimationRenderingSystem.h"

namespace Castlevania
{
	class DoorRenderingSystem : public AnimationRenderingSystem
	{
	public:
		DoorRenderingSystem(Door &parent, std::string animationPath);
		GameObject &GetParent() override;

	private:
		Door &parent;
		void OnMoveStateChanged() override;
	};
}
