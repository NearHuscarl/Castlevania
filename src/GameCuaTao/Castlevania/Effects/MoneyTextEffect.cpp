#include "MoneyTextEffect.h"

using namespace Castlevania;

constexpr auto MONEY_TEXT_EFFECT_LIFESPAN = 400;

MoneyTextEffect::MoneyTextEffect(std::shared_ptr<Texture> moneyTextTexture)
{
	this->moneyText = std::make_unique<Sprite>(moneyTextTexture);
}

void MoneyTextEffect::Show(Vector2 position)
{
	this->position = position;

	lifespanTimer.Start();
}

bool MoneyTextEffect::IsFinished()
{
	if (lifespanTimer.ElapsedMilliseconds() >= MONEY_TEXT_EFFECT_LIFESPAN)
		return true;

	return false;
}

void MoneyTextEffect::Update(GameTime gameTime)
{
}

void MoneyTextEffect::Draw(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(*moneyText, position);
}