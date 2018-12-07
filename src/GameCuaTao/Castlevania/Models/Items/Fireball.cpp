#include "Fireball.h"
#include "../UpdateData.h"

using namespace Castlevania;

Fireball::Fireball() : GameObject{ EntityType::Fireball }
{
}

int Fireball::GetAttack()
{
	return attack;
}

void Fireball::SetAttack(int attack)
{
	this->attack = attack;
}

void Fireball::Update(GameTime gameTime, UpdateData &updateData)
{
	GameObject::Update(gameTime, updateData);

	auto viewport = updateData.viewport;

	if (!viewport.TouchesOrIntersects(GetFrameRect()))
		Destroy();
}
