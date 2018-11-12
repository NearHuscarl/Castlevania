#include "Player.h"
#include "../../Settings/Button.h"

using namespace Castlevania;

Player::Player() : Simon(EntityType::Player)
{
	controller = std::make_unique<Controller>(*this);
}

IController *Player::GetController()
{
	return controller.get();
}