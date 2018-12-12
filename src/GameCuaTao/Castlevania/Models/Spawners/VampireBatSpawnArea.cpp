#include "Direct2DGame/MathHelper.h"
#include "VampireBatSpawnArea.h"
#include "../UpdateData.h"
#include "../Factories/ObjectFactory.h"

using namespace Castlevania;

VampireBatSpawnArea::VampireBatSpawnArea(ObjectFactory &objectFactory) :
	SpawnArea{ EntityType::VampireBat, objectFactory }
{
}

void VampireBatSpawnArea::SetGroupSpawnTime(int groupSpawnTime)
{
	this->originalGroupSpawnTime = groupSpawnTime;
	this->groupSpawnTime = originalGroupSpawnTime;
}

void VampireBatSpawnArea::SpawnObject(UpdateData &updateData)
{
	if (spawnGroupCount == 1) // Randomize groupSpawnTime before resetting group spawn timer
	{
		// In the original game, sometimes bat spawn time is much shorter than other times
		if (MathHelper::RandomPercent(20))
			groupSpawnTime = originalGroupSpawnTime / 3;
		else
			groupSpawnTime = originalGroupSpawnTime;
	}

	auto viewport = updateData.viewport;
	auto object = objectFactory.CreateEnemy(spawnObjectType);
	auto spawnPosition = Vector2{};
	auto facing = Facing{};

	if (MathHelper::RandomPercent(directionChances[Direction::Right]))
	{
		spawnPosition.x = viewport.right - object->GetFrameRect().Width();
		facing = Facing::Left;
	}
	else
	{
		spawnPosition.x = viewport.left;
		facing = Facing::Right;
	}

	auto playerBbox = updateData.objectCollection->player->GetBoundingBox();
	spawnPosition.y = playerBbox.bottom - playerBbox.Height() / 2 - object->GetFrameRect().Height() / 2;

	object->SetPosition(spawnPosition);
	object->SetFacing(facing);

	updateData.objectCollection->entities.push_back(std::move(object));
}
