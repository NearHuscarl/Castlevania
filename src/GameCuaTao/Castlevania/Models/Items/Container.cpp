#include "Container.h"
#include "../Settings.h"
#include "../../Models/UpdateData.h"
#include "../../Utilities/CollisionGrid.h"

using namespace Castlevania;

Container::Container(ObjectId type) : GameObject{ type }
{
	spawningState = ObjectState::DEAD;
}

void Container::SetSpawningState(ObjectState spawningState)
{
	this->spawningState = spawningState;
}

void Container::SetSpawnedItem(std::unique_ptr<Powerup> item)
{
	this->item = std::move(item);
}

void Container::OnBeingHit()
{
	if (spawningState == ObjectState::DYING)
	{
		auto spawnedItem = SpawnItem();

		if (spawnedItem != nullptr)
			collisionGrid->Add(std::move(spawnedItem), CollisionObjectType::Entity);
	}
	
	SetState(ObjectState::DYING);
	body.Enabled(false);
}

std::unique_ptr<GameObject> Container::SpawnItem()
{
	if (item != nullptr)
	{
		item->Spawn();
		item->SetOriginPosition(GetOriginPosition());
	}
	
	return std::move(item);
}

void Container::Update(UpdateData &updateData)
{
	GameObject::Update(updateData);
	
	if (state == ObjectState::DEAD && spawningState == ObjectState::DEAD)
	{
		auto spawnedItem = SpawnItem();

		if (spawnedItem != nullptr)
			collisionGrid->Add(std::move(spawnedItem), CollisionObjectType::Entity);
	}
}
