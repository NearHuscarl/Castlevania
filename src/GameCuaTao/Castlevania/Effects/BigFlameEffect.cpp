#include "BigFlameEffect.h"

using namespace Castlevania;

constexpr auto SPARK_LIFESPAN = 160;
constexpr auto FLAME_LIFESPAN = 800;

BigFlameEffect::BigFlameEffect(std::shared_ptr<AnimationFactory> flameAnimation)
{
	this->flame = std::make_unique<AnimatedSprite>(flameAnimation);

	flame->Play("FlameLoop");
	isFinished = true;
}

void BigFlameEffect::Show(Vector2 position)
{
	auto flameRect = flame->GetTextureRegion().GetFrameRectangle();

	this->position = Vector2{
		position.x - flameRect.Width() / 2,
		position.y - flameRect.Height() / 2 };

	flameLifespanTimer.Start();
	isFinished = false;
}

bool BigFlameEffect::IsFinished()
{
	return isFinished;
}

void BigFlameEffect::Update(GameTime gameTime)
{
	if (isFinished)
		return;

	flame->Update();

	if (flameLifespanTimer.ElapsedMilliseconds() >= FLAME_LIFESPAN)
		isFinished = true;
}

void BigFlameEffect::Draw(SpriteExtensions &spriteBatch)
{
	if (!IsFinished())
	{
		auto flameRect = flame->GetTextureRegion().GetFrameRectangle();
		auto flameWidth = flameRect.Width();
		auto flameHeight = flameRect.Height();

		spriteBatch.Draw(*flame, Vector2{ position.x - flameWidth, position.y - flameHeight });
		spriteBatch.Draw(*flame, Vector2{ position.x             , position.y - flameHeight });
		spriteBatch.Draw(*flame, Vector2{ position.x + flameWidth, position.y - flameHeight });
		spriteBatch.Draw(*flame, Vector2{ position.x - flameWidth, position.y               });
		spriteBatch.Draw(*flame, Vector2{ position.x             , position.y               });
		spriteBatch.Draw(*flame, Vector2{ position.x + flameWidth, position.y               });
	}
}