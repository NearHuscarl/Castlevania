#include "Brazier.h"
#include "../../Models/Factories/ObjectCollection.h"

using namespace Castlevania;

Brazier::Brazier() : GameObject{ EntityType::Brazier }
{
	isHit = false;
}

void Brazier::SetSpawnedItem(std::unique_ptr<Powerup> item)
{
	this->item = std::move(item);
}

void Brazier::SetHitEffect(std::unique_ptr<IEffect> effect)
{
	this->hitEffect = std::move(effect);
}

void Brazier::Update(GameTime gameTime, UpdateData &updateData)
{
	switch (state)
	{
		case BrazierState::Normal:
			GameObject::Update(gameTime, updateData);
			break;

		case BrazierState::Spawning:
			if (hitEffect->IsFinished())
			{
				isDestroyed = true;
				updateData.objectCollection->entities.push_back(SpawnItem());
			}
			break;
	}
}

void Brazier::Draw(SpriteExtensions &spriteBatch)
{
	switch (state)
	{
		case BrazierState::Normal:
			GameObject::Draw(spriteBatch);
			break;

		case BrazierState::Spawning:
			hitEffect->Draw(spriteBatch);
			break;
	}
}

void Brazier::OnBeingHit()
{
	state = BrazierState::Spawning;
	body.Enabled(false);
	hitEffect->Show(GetOriginPosition());
}

std::unique_ptr<GameObject> Brazier::SpawnItem()
{
	item->Spawn();
	item->SetOriginPosition(GetOriginPosition());
	isDestroyed = true;
	
	return std::move(item);
}
