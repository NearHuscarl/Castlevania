#include "FlameEffect.h"

using namespace Castlevania;

constexpr auto SPARK_LIFESPAN = 140;

FlameEffect::FlameEffect(std::shared_ptr<Texture> sparkTexture, std::shared_ptr<AnimationFactory> flameAnimation)
{
	this->spark = std::make_unique<Sprite>(sparkTexture);
	this->flame = std::make_unique<AnimatedSprite>(flameAnimation);

	isFinished = false;
}

void FlameEffect::Show(Vector2 position)
{
	auto flameRect = flame->GetTextureRegion().GetFrameRectangle();

	this->position = Vector2{
		position.x - flameRect.Width() / 2,
		position.y - flameRect.Height() / 2 };

	sparkLifespanTimer.Start();
}

bool FlameEffect::IsFinished()
{
	return isFinished;
}

void FlameEffect::Update(GameTime gameTime)
{
	if (isFinished)
		return;

	flame->Update();

	if (flame->AnimateComplete())
		isFinished = true;
}

void FlameEffect::Draw(SpriteExtensions &spriteBatch)
{
	if (sparkLifespanTimer.ElapsedMilliseconds() <= SPARK_LIFESPAN)
		spriteBatch.Draw(*spark, position);

	spriteBatch.Draw(*flame, position);
}