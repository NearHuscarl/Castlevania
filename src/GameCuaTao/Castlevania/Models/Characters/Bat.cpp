#include "Bat.h"

using namespace Castlevania;

Bat::Bat() : GameObject(EntityType::Bat)
{
}

void Bat::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>("Characters/NPCs/Bat.xml");
	sprite = std::make_unique<AnimatedSprite>(animationFactory);

	auto stats = content.Load<Dictionary>("CharacterStats/Bat.xml");
	auto speed = std::stof(stats->at("Speed"));
	auto animation = stats->at("StartingAnimation");

	SetLinearVelocity(speed);
	sprite->Play(animation);
}

void Bat::Draw(SpriteExtensions &spriteBatch)
{
	sprite->Update();
	spriteBatch.Draw(*sprite, position);
}