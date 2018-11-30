#include "Brazier.h"
#include "../Settings.h"
#include "../../Models/Factories/ObjectCollection.h"

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
