#include <vector>
#include "Direct2DGame/MathHelper.h"
#include "WhipRenderingSystem.h"
#include "Whip.h"

using namespace Castlevania;

WhipRenderingSystem::WhipRenderingSystem(Whip &parent, std::string spriteConfigPath) :
	parent{ parent }
{
	this->spriteConfigPath = spriteConfigPath;
}

RectF WhipRenderingSystem::GetBoundingBox()
{
	return sprite->GetBoundingRectangle(parent.GetPosition());
}

AnimatedSprite &WhipRenderingSystem::GetSprite()
{
	return *sprite;
}

void WhipRenderingSystem::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>(spriteConfigPath);
	auto animations_12 = std::vector<std::string> { "Whip_level_01", "Whip_level_02" }; // animation for level 1 and 2 whip

	sprite = std::make_unique<AnimatedSprite>(animationFactory, animations_12);
}

void WhipRenderingSystem::Update(float deltaTime)
{
	if (IsEnabledChanged())
	{
		OnEnabledChange();
	}

	if (!parent.GetBody().Enabled())
		return;

	sprite->Update();

	if (parent.GetFacing() == Facing::Left)
	{
		sprite->SetEffect(SpriteEffects::FlipHorizontally);
	}
	else
	{
		sprite->SetEffect(SpriteEffects::None);
	}
}

void WhipRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	if (!parent.GetBody().Enabled())
		return;

	spriteBatch.Draw(*sprite, parent.GetPosition());
}

bool WhipRenderingSystem::IsEnabledChanged()
{
	static auto enabled = parent.GetBody().Enabled();

	if (enabled != parent.GetBody().Enabled())
	{
		enabled = parent.GetBody().Enabled();
		return true;
	}

	return false;
}

void WhipRenderingSystem::OnEnabledChange()
{
	auto enabled = parent.GetBody().Enabled();
	auto level = MathHelper::Min(parent.GetLevel(), 2);

	if (enabled)
	{
		// Play level 1 or 2 whip animation, level 3 whip is another seperate object
		sprite->Play("Whip_level_0" + std::to_string(level));
	}
	else
	{
		sprite->GetCurrentAnimation().Reset();
	}
}
