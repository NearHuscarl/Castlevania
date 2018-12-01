#include "Dagger.h"

using namespace Castlevania;

Dagger::Dagger() : RangedWeapon{ EntityType::Dagger }
{
}

void Dagger::Update(GameTime gameTime, UpdateData &updateData)
{
	GameObject::Update(gameTime, updateData);

	auto viewport = updateData.viewport;

	if (!viewport.TouchesOrIntersects(GetFrameRect()))
		state = ObjectState::DEAD;
}
