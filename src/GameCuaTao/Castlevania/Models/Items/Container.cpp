#include "Container.h"
#include "Powerup.h"
#include "../Settings.h"
#include "../../Models/UpdateData.h"
#include "../../Utilities/CollisionGrid.h"

using namespace Castlevania;

Container::Container(ObjectId type, std::unique_ptr<PowerupGenerator> powerupGenerator) :
	GameObject{ type }
{
	this->spawningState = ObjectState::DEAD;
	this->powerupGenerator = std::move(powerupGenerator);
}

void Container::SetSpawningState(ObjectState spawningState)
{
	this->spawningState = spawningState;
}

void Container::SetSpawnedItem(ObjectId powerupType)
{
	this->powerupType = powerupType;
}

void Container::OnBeingHit()
{
	if (spawningState == ObjectState::DYING)
	{
		SpawnItem();
	}
	
	SetState(ObjectState::DYING);
	body.Enabled(false);
}

void Container::SpawnItem()
{
	if (powerupType == ObjectId::Unknown)
		return;

	auto item = powerupGenerator->Generate(powerupType);

	item->Spawn();
	item->SetOriginPosition(GetOriginPosition());
	collisionGrid->Add(std::move(item), CollisionObjectType::Entity);
}

void Container::Update(UpdateData &updateData)
{
	GameObject::Update(updateData);
	
	if (state == ObjectState::DEAD && spawningState == ObjectState::DEAD)
	{
		SpawnItem();
	}
}
