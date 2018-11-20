#include <vector>
#include "Direct2DGame/MathHelper.h"
#include "WhipFlashingRenderingSystem.h"
#include "Whip.h"

using namespace Castlevania;

WhipFlashingRenderingSystem::WhipFlashingRenderingSystem(Whip &parent, std::string spriteConfigPath) :
	parent{ parent }
{
	this->spriteConfigPath = spriteConfigPath;
}

RectF WhipFlashingRenderingSystem::GetBoundingBox()
{
	return spriteMagenta->GetBoundingRectangle(parent.GetPosition());
}

AnimatedSprite &WhipFlashingRenderingSystem::GetSprite()
{
	return *spriteMagenta;
}

void WhipFlashingRenderingSystem::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>(spriteConfigPath);

	auto animations_mangenta = std::vector<std::string>{ "Whip_level_03_magenta" };
	auto animations_red = std::vector<std::string>{ "Whip_level_03_red" };
	auto animations_yellow = std::vector<std::string>{ "Whip_level_03_yellow" };
	auto animations_blue = std::vector<std::string>{ "Whip_level_03_blue" };

	spriteMagenta = std::make_unique<AnimatedSprite>(animationFactory, animations_mangenta);
	spriteRed = std::make_unique<AnimatedSprite>(animationFactory, animations_red);
	spriteYellow = std::make_unique<AnimatedSprite>(animationFactory, animations_yellow);
	spriteBlue = std::make_unique<AnimatedSprite>(animationFactory, animations_blue);
}

void WhipFlashingRenderingSystem::Update(float deltaTime)
{
	if (IsEnabledChanged())
	{
		OnEnabledChange();
	}

	if (!parent.GetBody().Enabled())
		return;

	spriteMagenta->Update();
	spriteRed->Update();
	spriteYellow->Update();
	spriteBlue->Update();

	auto facing = parent.GetFacing();

	if (facing == Facing::Left)
	{
		spriteMagenta->SetEffect(SpriteEffects::FlipHorizontally);
		spriteRed->SetEffect(SpriteEffects::FlipHorizontally);
		spriteYellow->SetEffect(SpriteEffects::FlipHorizontally);
		spriteBlue->SetEffect(SpriteEffects::FlipHorizontally);
	}
	else
	{
		spriteMagenta->SetEffect(SpriteEffects::None);
		spriteRed->SetEffect(SpriteEffects::None);
		spriteYellow->SetEffect(SpriteEffects::None);
		spriteBlue->SetEffect(SpriteEffects::None);
	}

	auto randColor = MathHelper::RandomBetween(1, 4);
	while (randColor == currentColor)
	{
		randColor = MathHelper::RandomBetween(1, 4);
	}
	currentColor = randColor;
}

void WhipFlashingRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	if (!parent.GetBody().Enabled())
		return;

	switch (currentColor)
	{
		case 1:
			spriteBatch.Draw(*spriteMagenta, parent.GetPosition());
			break;
		case 2:
			spriteBatch.Draw(*spriteRed, parent.GetPosition());
			break;
		case 3:
			spriteBatch.Draw(*spriteYellow, parent.GetPosition());
			break;
		case 4:
			spriteBatch.Draw(*spriteBlue, parent.GetPosition());
			break;
	}
}

bool WhipFlashingRenderingSystem::IsEnabledChanged()
{
	static auto enabled = parent.GetBody().Enabled();

	if (enabled != parent.GetBody().Enabled())
	{
		enabled = parent.GetBody().Enabled();
		return true;
	}

	return false;
}

void WhipFlashingRenderingSystem::OnEnabledChange()
{
	auto enabled = parent.GetBody().Enabled();

	if (enabled)
	{
		spriteMagenta->Play("Whip_level_03_magenta");
		spriteRed->Play("Whip_level_03_red");
		spriteYellow->Play("Whip_level_03_yellow");
		spriteBlue->Play("Whip_level_03_blue");
	}
	else
	{
		spriteMagenta->GetCurrentAnimation().Reset();
		spriteRed->GetCurrentAnimation().Reset();
		spriteYellow->GetCurrentAnimation().Reset();
		spriteBlue->GetCurrentAnimation().Reset();
	}
}
