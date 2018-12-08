#pragma once

#include "Direct2DGame/GameTime.h"
#include "ISpawner.h"
#include "../GameObject.h"

namespace Castlevania
{
	class SpawnPoint : public GameObject, public ISpawner
	{
	public:
		SpawnPoint();

		void SetActive(bool value) override;
		void Update(GameTime gameTime);

	private:
		bool isActive;

		void SpawnObject(ObjectCollection &objectCollection) override;
	};
}