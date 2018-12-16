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
		SpawnArea(ObjectId spawnObjectType, ObjectFactory &objectFactory);

		SpawnState GetSpawnState() override;
		virtual void SetGroupSpawnTime(int groupSpawnTime);
		virtual void SetSpawnTime(int spawnTime);

		void SetDirectionChances(std::string directionChancesConfig);
		void SetDirectionChances(std::map<Direction, float> directionChances);
		void SetGroupCountChances(std::string groupCountChancesConfig);
		void SetGroupCountChances(std::map<int, float> groupCountChances);

		void Activate() override;
		void Deactivate() override;

		void Update(GameTime gameTime, UpdateData &updateData) override;

	protected:
		ObjectFactory &objectFactory;
		ObjectId spawnObjectType;

		SpawnState spawnState;
		int spawnGroupCount;
		int groupSpawnTime;
		int spawnTime;

		std::map<Direction, float> directionChances;
		std::map<int, float> groupCountChances;

		virtual void SpawnObject(UpdateData &updateData) = 0;

	private:
		Stopwatch groupSpawnTimer;
		Stopwatch spawnTimer;

		void StartSpawning();
		void StopSpawning();
	};
}