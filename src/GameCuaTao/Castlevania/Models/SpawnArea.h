#pragma once

#include "Direct2DGame/GameTime.h"
#include "GameObject.h"

namespace Castlevania
{
	class SpawnArea : public GameObject
	{
	public:
		SpawnArea();

		void SetActive(bool value);
		void Update(GameTime gameTime);

	private:
		bool isActive;
	};
}