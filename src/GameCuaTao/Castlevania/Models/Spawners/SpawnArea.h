#pragma once

#include "Direct2DGame/GameTime.h"
#include "Direct2DGame/Utilities/Stopwatch.h"
#include "ISpawner.h"
#include "../GameObject.h"

namespace Castlevania
{
	class ObjectFactory;

	enum class SpawnState
	{
		ACTIVE,
		INACTIVE,
		SPAWNING,
	};

	class SpawnArea : public GameObject, public ISpawner
	{
	public:
		SpawnArea(ObjectFactory &objectFactory);

		void SetSpawnGroupCount(int minSpawnGroup, int maxSpawnGroup = 0);
		void SetGroupSpawnTime(int minGroupSpawnTime, int maxGroupSpawnTime);
		void SetSpawnTime(int spawnTime);

		void Activate() override;
		void Deactivate() override;
		void Update(GameTime gameTime, UpdateData &updateData) override;

	protected:
		ObjectFactory &objectFactory;

		virtual void SpawnObject(ObjectCollection &objectCollection, RectF viewport) = 0;

	private:
		SpawnState spawnState;
		EntityType spawnedObjectType;

		int minSpawnGroup;
		int maxSpawnGroup;
		int minGroupSpawnTime;
		int maxGroupSpawnTime;
		int spawnTime;

		int groupSpawnTime;
		Stopwatch groupSpawnTimer;
		Stopwatch spawnTimer;
		int groupSpawnCount;

		void StartSpawning();
		void StopSpawning();
		void ResetGroupSpawnTimer();
	};
}