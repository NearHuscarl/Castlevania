#pragma once

#include "../GameObject.h"

namespace Castlevania
{
	class WaterArea : public GameObject
	{
	public:
		WaterArea();
		
		void Splash(Vector2 position);

	private:
		Vector2 splashPosition;

		friend class WaterAreaRenderingSystem;
	};
}