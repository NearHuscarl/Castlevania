#include "Container.h"
#include "../Settings.h"
#include "../../Models/UpdateData.h"

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
	item->Spawn();
	item->SetOriginPosition(GetOriginPosition());
	
	return std::move(item);
}

void Container::Update(GameTime gameTime, UpdateData &updateData)
{
	GameObject::Update(gameTime, updateData);

	if (state == ObjectState::DEAD)
		updateData.objectCollection->entities.push_back(SpawnItem());
}
