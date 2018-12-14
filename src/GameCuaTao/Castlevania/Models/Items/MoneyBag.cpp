#include "MoneyBag.h"

using namespace Castlevania;

MoneyBag::MoneyBag(int money, EntityType type) : Powerup{ type }
{
	this->money = money;
}

int MoneyBag::GetMoney()
{
	SetState(ObjectState::DYING);
	body.Enabled(false);

	// Disable body so this only collide with player once
	// But will make it fall through the floor and go outside
	// of viewport which make the effect text appear forever
	// (Anything outside of viewport is not updated) 
	// Quick solution: just remove the movement system to make the item stand still
	// TODO: implement spatial partition and remove the viewport optimization code
	Detach<IMovementSystem>();

	return money;
}
