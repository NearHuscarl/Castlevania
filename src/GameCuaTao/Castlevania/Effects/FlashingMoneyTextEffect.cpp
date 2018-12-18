#include "FlashingMoneyTextEffect.h"

using namespace Castlevania;

constexpr auto MONEY_TEXT_EFFECT_LIFESPAN = 400;

FlashingMoneyTextEffect::FlashingMoneyTextEffect(std::shared_ptr<AnimationFactory> moneyTextAnimation)
{
	this->moneyText = std::make_unique<AnimatedSprite>(moneyTextAnimation);
	isFinished = true;
}

void FlashingMoneyTextEffect::Show(Vector2 position)
{
	this->position = position;

	isFinished = false;
	lifespanTimer.Start();
}

bool FlashingMoneyTextEffect::IsFinished()
{
	return isFinished;
}

void FlashingMoneyTextEffect::Update(GameTime gameTime)
{
	if (isFinished)
		return;

	moneyText->Update();

	if (lifespanTimer.ElapsedMilliseconds() >= MONEY_TEXT_EFFECT_LIFESPAN)
		isFinished = true;
}

void FlashingMoneyTextEffect::Draw(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(*moneyText, position);
}