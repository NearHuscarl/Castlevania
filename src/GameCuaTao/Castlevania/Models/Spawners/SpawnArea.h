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
		virtual void SetSpawnGroupCount(int spawnGroup);
		virtual void SetGroupSpawnTime(int groupSpawnTime);
		virtual void SetSpawnTime(int spawnTime);

		void Activate() override;
		void Deactivate() override;

		void Update(GameTime gameTime, UpdateData &updateData) override;

	protected:
		ObjectFactory &objectFactory;
		EntityType spawnObjectType;

		SpawnState spawnState;
		int spawnGroupCount;
		int groupSpawnTime;
		int spawnTime;

		virtual void SpawnObject(UpdateData &updateData) = 0;

	private:
		int spawnGroupCountLeft;
		Stopwatch groupSpawnTimer;
		Stopwatch spawnTimer;

		void StartSpawning();
		void StopSpawning();
	};
}