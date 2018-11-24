#include "Bat.h"

using namespace Castlevania;

Bat::Bat() : GameObject(EntityType::Bat)
{
}

void Bat::LoadContent(ContentManager &content)
{
	GameObject::LoadContent(content);

	auto stats = content.Load<Dictionary>("CharacterStats/Bat.xml");
	auto speed = std::stof(stats->at("Speed"));

	SetLinearVelocity(speed);
}
