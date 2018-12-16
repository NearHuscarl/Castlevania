#include "Direct2DGame/MathHelper.h"
#include "FishmanSpawnArea.h"
#include "../UpdateData.h"
#include "../Characters/Enemies/Fishman.h"
#include "../Factories/ObjectFactory.h"

using namespace Castlevania;

constexpr auto MIN_OFFSET = 64;
constexpr auto MAX_OFFSET = 224;
constexpr auto MAX_FISHMAN_COUNT = 2;

FishmanSpawnArea::FishmanSpawnArea(ObjectFactory &objectFactory) :
	SpawnArea{ ObjectId::Fishman, objectFactory }
{
}

void FishmanSpawnArea::SpawnObject(UpdateData &updateData)
{
	auto &objectCollection = updateData.objectCollection;
	auto currentFishmanCount = 0;

	for (auto &entity : objectCollection->entities)
	{
		if (entity->GetId() == ObjectId::Fishman)
			currentFishmanCount++;
	}

	if (currentFishmanCount >= MAX_FISHMAN_COUNT)
		return;

	auto viewport = updateData.viewport;
	auto object = objectFactory.CreateEnemy(spawnObjectType);
	auto facing = Facing{};
	auto playerBbox = objectCollection->player->GetBoundingBox();
	auto randomOffset = MathHelper::RandomBetween(MIN_OFFSET, MAX_OFFSET);

	if (playerBbox.right + randomOffset >= viewport.right - object->GetFrameRect().Width())
		facing = Facing::Right;
	else if (playerBbox.left - randomOffset <= viewport.left)
		facing = Facing::Left;
	else
		facing = MathHelper::RandomBoolean() ? Facing::Left : Facing::Right;

	auto spawnPosition = Vector2{};

	if (facing == Facing::Left)
		spawnPosition.x = playerBbox.right + randomOffset;
	else // facing == Facing::Right
		spawnPosition.x = playerBbox.left - randomOffset;

	spawnPosition.y = GetBoundingBox().bottom - object->GetFrameRect().Height();
	object->SetPosition(spawnPosition);
	object->SetFacing(facing);
	static_cast<Fishman&>(*object).Launch();

	objectCollection->entities.push_back(std::move(object));
}
