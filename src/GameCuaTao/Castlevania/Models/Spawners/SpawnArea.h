#pragma once

#include "Direct2DGame/GameTime.h"
#include "Direct2DGame/Utilities/Stopwatch.h"
#include "ISpawner.h"
#include "../GameObject.h"

namespace Castlevania
{
	class ObjectFactory;

	class SpawnArea : public GameObject, public ISpawner
	{
	public:
		SpawnArea(EntityType spawnObjectType, ObjectFactory &objectFactory);

		SpawnState GetSpawnState() override;
		void SetSpawnGroupCount(int spawnGroup);
		void SetGroupSpawnTime(int groupSpawnTime);
		void SetSpawnTime(int spawnTime);

		void Activate() override;
		void Deactivate() override;

		void Update(GameTime gameTime, UpdateData &updateData) override;

	protected:
		ObjectFactory &objectFactory;
		EntityType spawnObjectType;

		virtual void SpawnObject(UpdateData &updateData) = 0;
		std::unique_ptr<GameObject> Spawn();

	private:
		SpawnState spawnState;
		int spawnGroupCount;
		int groupSpawnTime;
		int spawnTime;

		int spawnGroupCountLeft;
		Stopwatch groupSpawnTimer;
		Stopwatch spawnTimer;

		void StartSpawning();
		void StopSpawning();
	};
}