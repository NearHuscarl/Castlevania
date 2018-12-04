#include "PantherRenderingSystem.h"
#include "../../Settings.h"
#include "../../../Settings/Animations.h"

using namespace Castlevania;

PantherRenderingSystem::PantherRenderingSystem(
	Panther &parent,
	std::string animationPath,
	std::unique_ptr<IEffect> effect)
	:
	parent{ parent }
{
	this->animationPath = animationPath;
	hitEffect = std::move(effect);
}

Sprite &PantherRenderingSystem::GetSprite()
{
	return *sprite;
}

GameObject &PantherRenderingSystem::GetParent()
{
	return parent;
}

void PantherRenderingSystem::Receive(int message)
{
	switch (message)
	{
		case MOVE_STATE_CHANGED:
			OnMoveStateChanged();
			break;

		case STATE_CHANGED:
			OnStateChanged();
	}
}

void PantherRenderingSystem::LoadContent(ContentManager &content)
{
	RenderingSystem::LoadContent(content);
	auto animations = content.Load<AnimationFactory>(animationPath);
	sprite = std::make_unique<AnimatedSprite>(animations);
}

void PantherRenderingSystem::Update(GameTime gameTime)
{
	auto pantherState = parent.GetPantherState();
	auto velocity = parent.GetVelocity();

	switch (parent.GetState())
	{
		case ObjectState::NORMAL:
			sprite->Update();
			break;

		case ObjectState::DYING:
			if (hitEffect->IsFinished())
				parent.Destroy();
			break;
	}
}

void PantherRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	RenderingSystem::Draw(spriteBatch);

	DrawBoundingBox(spriteBatch, parent.GetActiveArea(), Color::LavenderBlue() * 0.4f); // TODO: remove debugging code

	switch (parent.GetState())
	{
		case ObjectState::NORMAL:
			spriteBatch.Draw(*sprite, parent.GetPosition());
			break;

		case ObjectState::DYING:
			hitEffect->Draw(spriteBatch);
			break;
	}
}

void PantherRenderingSystem::OnMoveStateChanged()
{
	switch (parent.GetPantherState())
	{
		case PantherState::IDLE:
			sprite->Play(IDLE_ANIMATION);
			break;

		case PantherState::RUNNING:
			sprite->Play(RUN_ANIMATION);
			break;

		case PantherState::JUMPING:
			sprite->Play(JUMP_ANIMATION);
			break;
	}
}

void PantherRenderingSystem::OnStateChanged()
{
	if (parent.GetState() == ObjectState::DYING)
		hitEffect->Show(parent.GetOriginPosition());
}
