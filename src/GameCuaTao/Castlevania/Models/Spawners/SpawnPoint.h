#pragma once

#include "Direct2DGame/GameTime.h"
#include "ISpawner.h"
#include "../GameObject.h"

namespace Castlevania
{
	class ObjectFactory;

	class SpawnPoint : public GameObject, public ISpawner
	{
	public:
		SpawnPoint(EntityType spawnObjectType, ObjectFactory &objectFactory);

		SpawnState GetSpawnState() override;
		void Update(GameTime gameTime, UpdateData &updateData) override;

	private:
		ObjectFactory &objectFactory;
		EntityType spawnObjectType;
		SpawnState spawnState;

		void Activate() override;
		void Deactivate() override;
	};
}