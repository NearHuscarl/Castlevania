#include "MoneyTextEffect.h"

using namespace Castlevania;

constexpr auto MONEY_TEXT_EFFECT_LIFESPAN = 400;

MoneyTextEffect::MoneyTextEffect(std::shared_ptr<Texture> moneyTextTexture)
{
	this->moneyText = std::make_unique<Sprite>(moneyTextTexture);
	isFinished = true;
}

void MoneyTextEffect::Show(Vector2 position)
{
	this->position = position;

	isFinished = false;
	lifespanTimer.Start();
}

bool MoneyTextEffect::IsFinished()
{
	return isFinished;
}

void MoneyTextEffect::Update(GameTime gameTime)
{
	if (lifespanTimer.ElapsedMilliseconds() >= MONEY_TEXT_EFFECT_LIFESPAN)
		isFinished = true;
}

void MoneyTextEffect::Draw(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(*moneyText, position);
}