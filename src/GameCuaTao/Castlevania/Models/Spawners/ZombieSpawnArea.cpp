#include "Direct2DGame/MathHelper.h"
#include "ZombieSpawnArea.h"
#include "../Factories/ObjectCollection.h"
#include "../Factories/ObjectFactory.h"

using namespace Castlevania;

ZombieSpawnArea::ZombieSpawnArea(ObjectFactory &objectFactory) : SpawnArea{ objectFactory }
{
}

void ZombieSpawnArea::SpawnObject(ObjectCollection &objectCollection, RectF viewport)
{
	auto object = objectFactory.CreateZombie();
	auto spawnPosition = Vector2{};
	auto facing = Facing{};

	// 80% chance to spawn on the right side because that's where the simon is heading to
	if (MathHelper::RandomPercent(80))
	{
		spawnPosition.x = viewport.right - object->GetFrameRect().Width();
		facing = Facing::Left;
	}
	else
	{
		spawnPosition.x = viewport.left;
		facing = Facing::Right;
	}

	// -1: to make object barely hit the ground or it will fall through it
	spawnPosition.y = GetBoundingBox().bottom - object->GetFrameRect().Height() - 1;
	object->SetPosition(spawnPosition);
	object->SetFacing(facing);

	objectCollection.entities.push_back(std::move(object));
}
