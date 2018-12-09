#include "Direct2DGame/MathHelper.h"
#include "VampireBatSpawnArea.h"
#include "../UpdateData.h"
#include "../Factories/ObjectFactory.h"

using namespace Castlevania;

VampireBatSpawnArea::VampireBatSpawnArea(ObjectFactory &objectFactory) :
	SpawnArea{ EntityType::VampireBat, objectFactory }
{
}

void VampireBatSpawnArea::SpawnObject(UpdateData &updateData)
{
	auto viewport = updateData.viewport;
	auto object = objectFactory.CreateEnemy(spawnObjectType);
	auto spawnPosition = Vector2{};
	auto facing = Facing{};

	if (MathHelper::RandomPercent(75))
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
