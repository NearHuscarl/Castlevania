#include "Bat.h"

using namespace Castlevania;

void Bat::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>("Characters/NPCs/BatAnimationDef.xml");
	sprite = std::make_unique<AnimatedSprite>(animationFactory);
	auto stats = content.Load<CharacterStats>("CharacterStats/Bat.xml");

	speed = stats->speed;
	velocity = speed;

	sprite->Play(stats->startingAnimation);
}

void Bat::Update(float deltaTime)
{
	GameObject::UpdateDistance(deltaTime);
	sprite->Update(deltaTime);
}

void Bat::Draw(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(*sprite, transform);
}