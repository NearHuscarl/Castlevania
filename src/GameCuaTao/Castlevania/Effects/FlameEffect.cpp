#include "FlameEffect.h"

using namespace Castlevania;

constexpr auto SPARK_LIFESPAN = 140;

FlameEffect::FlameEffect(std::shared_ptr<Texture> sparkTexture, std::shared_ptr<AnimationFactory> flameAnimation)
{
	this->spark = std::make_unique<Sprite>(sparkTexture);
	this->flame = std::make_unique<AnimatedSprite>(flameAnimation);
}

void FlameEffect::Show(Vector2 position)
{
	auto flameRect = flame->GetFrameRectangle(position);
	this->position = Vector2{ position.x - flameRect.Width() / 2, position.y - flameRect.Height() / 2 };

	sparkLifespanTimer.Start();
}

bool FlameEffect::IsFinished()
{
	if (flame->AnimateComplete())
		return true;

	return false;
}

void FlameEffect::Draw(SpriteExtensions &spriteBatch)
{
	if (sparkLifespanTimer.ElapsedMilliseconds() <= SPARK_LIFESPAN)
		spriteBatch.Draw(*spark, position);

	flame->Update();
	spriteBatch.Draw(*flame, position);
}