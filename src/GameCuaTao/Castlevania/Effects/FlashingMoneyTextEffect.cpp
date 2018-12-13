#include "FlashingMoneyTextEffect.h"

using namespace Castlevania;

constexpr auto MONEY_TEXT_EFFECT_LIFESPAN = 400;

FlashingMoneyTextEffect::FlashingMoneyTextEffect(std::shared_ptr<AnimationFactory> moneyTextAnimation)
{
	this->moneyText = std::make_unique<AnimatedSprite>(moneyTextAnimation);
}

void FlashingMoneyTextEffect::Show(Vector2 position)
{
	this->position = position;

	lifespanTimer.Start();
}

bool FlashingMoneyTextEffect::IsFinished()
{
	if (lifespanTimer.ElapsedMilliseconds() >= MONEY_TEXT_EFFECT_LIFESPAN)
		return true;

	return false;
}

void FlashingMoneyTextEffect::Draw(SpriteExtensions &spriteBatch)
{
	moneyText->Update();
	spriteBatch.Draw(*moneyText, position);
}