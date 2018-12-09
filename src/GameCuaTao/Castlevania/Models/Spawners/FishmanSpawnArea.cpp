#include "Direct2DGame/MathHelper.h"
#include "FishmanSpawnArea.h"
#include "../UpdateData.h"
#include "../Characters/Enemies/Fishman.h"
#include "../Factories/ObjectFactory.h"

using namespace Castlevania;

constexpr auto MIN_OFFSET = 64;
constexpr auto MAX_OFFSET = 224;

FishmanSpawnArea::FishmanSpawnArea(ObjectFactory &objectFactory) :
	SpawnArea{ EntityType::Fishman, objectFactory }
{
}

void FishmanSpawnArea::SpawnObject(UpdateData &updateData)
{
	auto viewport = updateData.viewport;
	auto object = objectFactory.CreateEnemy(spawnObjectType);
	auto spawnPosition = Vector2{};
	auto facing = Facing{};
	auto playerBbox = updateData.objectCollection->player->GetBoundingBox();
	auto randomOffset = MathHelper::RandomBetween(MIN_OFFSET, MAX_OFFSET);

	if (playerBbox.right + randomOffset >= viewport.right - object->GetFrameRect().Width())
		facing = Facing::Right;
	else if (playerBbox.left - randomOffset <= viewport.left)
		facing = Facing::Left;
	else
		facing = MathHelper::RandomBoolean() ? Facing::Left : Facing::Right;

	if (facing == Facing::Left)
		spawnPosition.x = playerBbox.right + randomOffset;
	else // facing == Facing::Right
		spawnPosition.x = playerBbox.left - randomOffset;

	spawnPosition.y = GetBoundingBox().bottom - object->GetFrameRect().Height();
	object->SetPosition(spawnPosition);
	object->SetFacing(facing);
	dynamic_cast<Fishman&>(*object).Launch();

	updateData.objectCollection->entities.push_back(std::move(object));
}
