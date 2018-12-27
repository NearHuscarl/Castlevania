#include "DebrisEffect.h"
#include "../Models/Settings.h"

using namespace Castlevania;

constexpr auto EFFECT_LIFESPAN = 2000;

DebrisEffect::DebrisEffect(std::shared_ptr<Texture> debrisTexture)
{
	debris = std::make_unique<Sprite>(debrisTexture);

	debrisTopLeftVelocity = Vector2{ 100, -250 };
	debrisTopRightVelocity = Vector2{ 120, -300 };
	debrisBottomLeftVelocity = Vector2{ -100, -300 };
	debrisBottomRightVelocity = Vector2{ 50, -200 };

	isFinished = true;
}

void DebrisEffect::Show(Vector2 position)
{
	auto debrisRect = debris->GetTextureRegion().GetFrameRectangle();
	auto debrisPosition = Vector2{
		position.x - debrisRect.Width() / 2,
		position.y - debrisRect.Height() / 2 };

	auto debrisTopPosition = Vector2{ debrisPosition.x, debrisPosition.y - 15 };
	auto debrisBottomPosition = Vector2{ debrisPosition.x, debrisPosition.y + 15 };

	debrisTopLeftPosition = debrisTopPosition;
	debrisTopRightPosition = debrisTopPosition;
	debrisBottomLeftPosition = debrisBottomPosition;
	debrisBottomRightPosition = debrisBottomPosition;

	isFinished = false;
	lifespanTimer.Start();
}

bool DebrisEffect::IsFinished()
{
	return isFinished;
}

void DebrisEffect::Update(GameTime gameTime)
{
	if (isFinished)
		return;

	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	debrisTopLeftVelocity.y += GRAVITY;
	debrisTopRightVelocity.y += GRAVITY;
	debrisBottomLeftVelocity.y += GRAVITY;
	debrisBottomRightVelocity.y += GRAVITY;
	
	debrisTopLeftPosition += debrisTopLeftVelocity * deltaTime;
	debrisTopRightPosition += debrisTopRightVelocity * deltaTime;
	debrisBottomLeftPosition += debrisBottomLeftVelocity * deltaTime;
	debrisBottomRightPosition += debrisBottomRightVelocity * deltaTime;

	if (lifespanTimer.ElapsedMilliseconds() >= EFFECT_LIFESPAN)
		isFinished = true;
}

void DebrisEffect::Draw(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(*debris, debrisTopLeftPosition);
	spriteBatch.Draw(*debris, debrisTopRightPosition);
	spriteBatch.Draw(*debris, debrisBottomLeftPosition);
	spriteBatch.Draw(*debris, debrisBottomRightPosition);
}