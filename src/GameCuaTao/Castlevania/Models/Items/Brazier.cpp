#include "Brazier.h"
#include "../Settings.h"
#include "../../Models/UpdateData.h"

using namespace Castlevania;

Brazier::Brazier() : GameObject{ EntityType::Brazier }
{
}

void Brazier::SetSpawnedItem(std::unique_ptr<Powerup> item)
{
	this->item = std::move(item);
}

void Brazier::OnBeingHit()
{
	SetState(ObjectState::DYING);
	body.Enabled(false);
}

std::unique_ptr<GameObject> Brazier::SpawnItem()
{
	item->Spawn();
	item->SetOriginPosition(GetOriginPosition());
	
	return std::move(item);
}

void Brazier::Update(GameTime gameTime, UpdateData &updateData)
{
	GameObject::Update(gameTime, updateData);

	if (state == ObjectState::DEAD)
		updateData.objectCollection->entities.push_back(SpawnItem());
}
