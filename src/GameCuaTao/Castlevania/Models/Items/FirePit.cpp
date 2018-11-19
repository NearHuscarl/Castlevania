#include "FirePit.h"

using namespace Castlevania;

FirePit::FirePit() : AnimatedObject(EntityType::FirePit)
{
}

void FirePit::SetSpawnedItem(std::unique_ptr<GameObject> item)
{
	this->item = std::move(item);
}

void FirePit::LoadContent(ContentManager &content)
{
	AnimatedObject::LoadContent(content);
}

void FirePit::Update(float deltaTime, ObjectCollection *objectCollection)
{
	AnimatedObject::Update(deltaTime, objectCollection);
}

std::unique_ptr<GameObject> FirePit::SpawnItem()
{
	body.Enabled(false);

	return std::move(item);
}
