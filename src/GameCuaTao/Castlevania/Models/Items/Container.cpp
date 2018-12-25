#include "Container.h"
#include "../Settings.h"
#include "../../Models/UpdateData.h"
#include "../../Utilities/CollisionGrid.h"

using namespace Castlevania;

Container::Container() : GameObject{ ObjectId::Brazier }
{
}

void Container::SetSpawnedItem(std::unique_ptr<Powerup> item)
{
	this->item = std::move(item);
}

void Container::OnBeingHit()
{
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
	
	if (state == ObjectState::DEAD)
	{
		auto spawnedItem = SpawnItem();

		if (spawnedItem != nullptr)
			collisionGrid->Add(std::move(spawnedItem), CollisionObjectType::Entity);
	}
}
