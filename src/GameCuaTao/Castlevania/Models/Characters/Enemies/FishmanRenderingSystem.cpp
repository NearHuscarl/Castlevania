#include "FishmanRenderingSystem.h"
#include "../../Settings.h"
#include "../../../Settings/Animations.h"

using namespace Castlevania;

FishmanRenderingSystem::FishmanRenderingSystem(
	Fishman &parent,
	std::string animationPath,
	std::unique_ptr<IEffect> dieEffect,
	std::unique_ptr<IEffect> launchEffect)
	:
	EffectRenderingSystem{ parent, animationPath, std::move(dieEffect) },
	parent{ parent }
{
	this->launchEffect = std::move(launchEffect);
}

void FishmanRenderingSystem::Update(GameTime gameTime)
{
	EffectRenderingSystem::Update(gameTime);

	switch (parent.GetFishmanState())
	{
		case FishmanState::LAUNCHING:
			launchEffect->Update(gameTime);
			break;
	}
}

void FishmanRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	EffectRenderingSystem::Draw(spriteBatch);

	switch (parent.GetFishmanState())
	{
		case FishmanState::LAUNCHING:
			launchEffect->Draw(spriteBatch);
			break;
	}
}

void FishmanRenderingSystem::OnMoveStateChanged()
{
	switch (parent.GetFishmanState())
	{
		case FishmanState::LAUNCHING:
			sprite->Play(IDLE_ANIMATION);
			launchEffect->Show(parent.GetOriginPosition());
			break;

		case FishmanState::WALKING:
			sprite->PlayCached(WALK_ANIMATION);
			break;

		case FishmanState::FALLING:
			sprite->GetCurrentAnimation().Stop();
			break;

		case FishmanState::SHOOTING:
			sprite->Play(SHOOT_ANIMATION);
			break;
	}
}
