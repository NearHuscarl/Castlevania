#include <vector>
#include "Direct2DGame/MathHelper.h"
#include "WhipFlashingRenderingSystem.h"
#include "Whip.h"
#include "WhipSettings.h"

using namespace Castlevania;

WhipFlashingRenderingSystem::WhipFlashingRenderingSystem(Whip &parent, std::string spriteConfigPath) :
	WhipRenderingSystem{ parent, spriteConfigPath }
{
}

void WhipFlashingRenderingSystem::Receive(int message)
{
	WhipRenderingSystem::Receive(message);

	if (message == WHIP_FACING_CHANGED)
		OnFacingChanged();
}

void WhipFlashingRenderingSystem::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>(spriteConfigPath);

	auto animations_mangenta = std::vector<std::string>{ "Whip_level_03_magenta" };
	auto animations_red = std::vector<std::string>{ "Whip_level_03_red" };
	auto animations_yellow = std::vector<std::string>{ "Whip_level_03_yellow" };
	auto animations_blue = std::vector<std::string>{ "Whip_level_03_blue" };

	sprite = std::make_unique<AnimatedSprite>(animationFactory, animations_mangenta);
	spriteRed = std::make_unique<AnimatedSprite>(animationFactory, animations_red);
	spriteYellow = std::make_unique<AnimatedSprite>(animationFactory, animations_yellow);
	spriteBlue = std::make_unique<AnimatedSprite>(animationFactory, animations_blue);
}

void WhipFlashingRenderingSystem::Update(GameTime gameTime)
{
	if (!parent.GetBody().Enabled())
		return;

	sprite->Update();
	spriteRed->Update();
	spriteYellow->Update();
	spriteBlue->Update();
	UpdatePositionRelativeToPlayer();

	auto facing = parent.GetFacing();

	currentColor = MathHelper::RandomBetween(1, 4, currentColor);
}

void WhipFlashingRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	if (!parent.GetBody().Enabled())
		return;

	switch (currentColor)
	{
		case 1:
			spriteBatch.Draw(*sprite, parent.GetPosition());
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

void WhipFlashingRenderingSystem::OnEnabledChanged()
{
	UpdatePositionRelativeToPlayer();

	auto enabled = parent.GetBody().Enabled();

	if (enabled)
	{
		sprite->Play("Whip_level_03_magenta");
		spriteRed->Play("Whip_level_03_red");
		spriteYellow->Play("Whip_level_03_yellow");
		spriteBlue->Play("Whip_level_03_blue");
	}
	else
	{
		sprite->GetCurrentAnimation().Reset();
		spriteRed->GetCurrentAnimation().Reset();
		spriteYellow->GetCurrentAnimation().Reset();
		spriteBlue->GetCurrentAnimation().Reset();
	}
}

void WhipFlashingRenderingSystem::OnFacingChanged()
{
	if (parent.GetFacing() == Facing::Left)
	{
		sprite->SetEffect(SpriteEffects::FlipHorizontally);
		spriteRed->SetEffect(SpriteEffects::FlipHorizontally);
		spriteYellow->SetEffect(SpriteEffects::FlipHorizontally);
		spriteBlue->SetEffect(SpriteEffects::FlipHorizontally);
	}
	else
	{
		sprite->SetEffect(SpriteEffects::None);
		spriteRed->SetEffect(SpriteEffects::None);
		spriteYellow->SetEffect(SpriteEffects::None);
		spriteBlue->SetEffect(SpriteEffects::None);
	}
}
