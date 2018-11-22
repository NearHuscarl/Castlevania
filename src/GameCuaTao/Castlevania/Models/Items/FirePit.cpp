#include "FirePit.h"
#include "../../Factories/ObjectCollection.h"

using namespace Castlevania;

FirePit::FirePit() : GameObject(EntityType::FirePit)
{
	isHit = false;
}

void FirePit::SetSpawnedItem(std::unique_ptr<Powerup> item)
{
	this->item = std::move(item);
}

void FirePit::SetHitEffect(std::unique_ptr<IEffect> effect)
{
	this->hitEffect = std::move(effect);
}

void Castlevania::FirePit::Update(float deltaTime, ObjectCollection *objectCollection)
{
	switch (state)
	{
		case FirePitState::Normal:
			GameObject::Update(deltaTime, objectCollection);
			break;

		case FirePitState::Spawning:
			if (hitEffect->IsFinished())
			{
				isDestroyed = true;
				objectCollection->entities.push_back(SpawnItem());
			}
			break;
	}
}

void FirePit::Draw(SpriteExtensions &spriteBatch)
{
	switch (state)
	{
		case FirePitState::Normal:
			GameObject::Draw(spriteBatch);
			break;

		case FirePitState::Spawning:
			hitEffect->Draw(spriteBatch);
			break;
	}
}

void FirePit::OnBeingHit()
{
	state = FirePitState::Spawning;
	body.Enabled(false);
	hitEffect->Show(GetOriginPosition());
}

std::unique_ptr<GameObject> FirePit::SpawnItem()
{
	item->Spawn();
	item->SetOriginPosition(GetOriginPosition());
	isDestroyed = true;
	
	return std::move(item);
}
