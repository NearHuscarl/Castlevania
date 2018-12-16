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
		SpawnPoint(ObjectId spawnObjectType, ObjectFactory &objectFactory);

		SpawnState GetSpawnState() override;
		void Update(GameTime gameTime, UpdateData &updateData) override;

	private:
		ObjectFactory &objectFactory;
		ObjectId spawnObjectType;
		SpawnState spawnState;

		void Activate() override;
		void Deactivate() override;
	};
}