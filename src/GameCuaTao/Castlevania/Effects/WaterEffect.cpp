#include "WaterEffect.h"
#include "../Models/Settings.h"

using namespace Castlevania;

constexpr auto WATER_EFFECT_LIFESPAN = 2000;

WaterEffect::WaterEffect(std::shared_ptr<Texture> waterTexture)
{
	water = std::make_unique<Sprite>(waterTexture);

	dropletLeftVelocity = Vector2{ -50, -200 };
	dropletTopVelocity = Vector2{ 25, -400 };
	dropletRightVelocity = Vector2{ 50, -200 };

	isFinished = true;
}

void WaterEffect::Show(Vector2 position)
{
	auto waterRect = water->GetTextureRegion().GetFrameRectangle();
	auto waterPosition = Vector2{
		position.x - waterRect.Width() / 2,
		position.y - waterRect.Height() / 2 };

	dropletLeftPosition = waterPosition;
	dropletTopPosition = waterPosition;
	dropletRightPosition = waterPosition;

	isFinished = false;
	lifespanTimer.Start();
}

bool WaterEffect::IsFinished()
{
	return isFinished;
}

void WaterEffect::Update(GameTime gameTime)
{
	if (isFinished)
		return;

	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	dropletLeftVelocity.y += GRAVITY;
	dropletTopVelocity.y += GRAVITY;
	dropletRightVelocity.y += GRAVITY;

	dropletLeftPosition += dropletLeftVelocity * deltaTime;
	dropletTopPosition += dropletTopVelocity * deltaTime;
	dropletRightPosition += dropletRightVelocity * deltaTime;

	if (lifespanTimer.ElapsedMilliseconds() >= WATER_EFFECT_LIFESPAN)
		isFinished = true;
}

void WaterEffect::Draw(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(*water, dropletLeftPosition);
	spriteBatch.Draw(*water, dropletTopPosition);
	spriteBatch.Draw(*water, dropletRightPosition);
}