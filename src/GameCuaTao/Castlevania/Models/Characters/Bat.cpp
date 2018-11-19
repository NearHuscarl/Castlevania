#include "Bat.h"

using namespace Castlevania;

Bat::Bat() : AnimatedObject(EntityType::Bat)
{
}

void Bat::LoadContent(ContentManager &content)
{
	AnimatedObject::LoadContent(content);

	auto stats = content.Load<Dictionary>("CharacterStats/Bat.xml");
	auto speed = std::stof(stats->at("Speed"));
	auto animation = stats->at("StartingAnimation");

	SetLinearVelocity(speed);
	GetSprite().Play(animation);
}