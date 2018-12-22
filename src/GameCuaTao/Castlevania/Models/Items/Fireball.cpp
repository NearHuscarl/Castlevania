#include "Fireball.h"
#include "../UpdateData.h"

using namespace Castlevania;

Fireball::Fireball() : GameObject{ ObjectId::Fireball }
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

void Fireball::Update(UpdateData &updateData)
{
	GameObject::Update(updateData);

	auto viewport = updateData.viewport;

	if (!viewport.TouchesOrIntersects(GetFrameRect()))
		Destroy();
}
