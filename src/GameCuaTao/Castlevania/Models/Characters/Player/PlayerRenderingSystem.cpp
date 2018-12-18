#include "PlayerRenderingSystem.h"
#include "../../Settings.h"
#include "../../../Settings/Animations.h"
#include "../../../Scenes/Stages/StageEvent.h"

using namespace Castlevania;

constexpr auto BEND_KNEE_ON_JUMPING_Y = 330.0f;
constexpr auto STRETCH_LEG_ON_FALLING_Y = 200.0f;

PlayerRenderingSystem::PlayerRenderingSystem(Player &parent, std::string animationPath) :
	parent{ parent }
{
	this->animationPath = animationPath;
}

Sprite &PlayerRenderingSystem::GetSprite()
{
	return *sprite;
}

GameObject &PlayerRenderingSystem::GetParent()
{
	return parent;
}

void PlayerRenderingSystem::Receive(int message)
{
	switch (message)
	{
		case STATE_CHANGED:
			OnStateChanged();
			break;

		case MOVE_STATE_CHANGED:
			OnMoveStateChanged();
			break;

		case ATTACK_STATE_CHANGED:
			OnAttackStateChanged();
			break;

		case UNTOUCHABLE_ENDED:
			OnUntouchableFinish();
			break;
	}
}

void PlayerRenderingSystem::LoadContent(ContentManager &content)
{
	RenderingSystem::LoadContent(content);
	auto animations = content.Load<AnimationFactory>(animationPath);
	sprite = std::make_unique<AnimatedSprite>(animations);
}

void PlayerRenderingSystem::Update(GameTime gameTime)
{
	switch (parent.state)
	{
		case ObjectState::NORMAL:
			UpdateNormalState();
			break;

		case ObjectState::DYING:
			if (sprite->AnimateComplete())
				parent.Notify(PLAYER_DIE);
			break;
	}

	sprite->Update();
}

void PlayerRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	RenderingSystem::Draw(spriteBatch);
	spriteBatch.Draw(*sprite, parent.GetPosition());
}

void PlayerRenderingSystem::UpdateNormalState()
{
	auto moveState = parent.GetMoveState();
	auto attackState = parent.GetAttackState();
	auto velocity = parent.GetVelocity();

	switch (attackState)
	{
		case AttackState::INACTIVE:
			switch (moveState)
			{
				case MoveState::GOING_UPSTAIRS:
				case MoveState::GOING_DOWNSTAIRS:
					if (sprite->AnimateComplete()) // finish the rest of climbing animation
						parent.Idle();
					break;

				case MoveState::JUMPING:
				case MoveState::HOVERING:
				case MoveState::FALLING:
					if (velocity.y > -BEND_KNEE_ON_JUMPING_Y)
						sprite->Play(JUMP_ANIMATION);

					if (velocity.y > STRETCH_LEG_ON_FALLING_Y)
						sprite->Play(IDLE_ANIMATION);
					break;
			}
			break;

		case AttackState::THROWING:
			// the animation frame in which simon is throwing
			if (sprite->GetCurrentAnimation().GetCurrentFrameIndex() == 2)
				parent.DoThrow();

		case AttackState::WHIPPING:
			if (sprite->AnimateComplete())
				parent.OnAttackComplete();
			break;
	}

	if (parent.untouchableTimer.IsRunning())
	{
		if (parent.GetMoveState() != MoveState::TAKING_DAMAGE)
			sprite->SetVisibility(Stopwatch::Every(1) ? true : false);
	}
}

void PlayerRenderingSystem::OnStateChanged()
{
	switch (parent.state)
	{
		case ObjectState::DYING:
			sprite->Play(DIE_ANIMATION);
			break;
	}
}

void PlayerRenderingSystem::OnMoveStateChanged()
{
	switch (parent.moveState)
	{
		case MoveState::IDLE:
			sprite->Play(IDLE_ANIMATION);
			break;

		case MoveState::WALKING:
		case MoveState::WALKING_TO_STAIRS:
			sprite->PlayCached(WALK_ANIMATION);
			break;

		case MoveState::IDLE_UPSTAIRS:
			sprite->Play(IDLE_UPSTAIRS_ANIMATION);
			break;

		case MoveState::IDLE_DOWNSTAIRS:
			sprite->Play(IDLE_DOWNSTAIRS_ANIMATION);
			break;

		case MoveState::GOING_UPSTAIRS:
			sprite->Play(GO_UPSTAIRS_ANIMATION);
			break;

		case MoveState::GOING_DOWNSTAIRS:
			sprite->Play(GO_DOWNSTAIRS_ANIMATION);
			break;

		case MoveState::DUCKING:
		case MoveState::LANDING_HARD:
			sprite->Play(DUCK_ANIMATION);
			break;

		case MoveState::LANDING:
			sprite->Play(JUMP_ANIMATION);
			break;

		case MoveState::FLASHING:
		{
			auto currentFrameIndex = sprite->GetCurrentAnimation().GetCurrentFrameIndex();

			switch (currentFrameIndex)
			{
				case 0:
					sprite->Play(FLASH_01_ANIMATION);
					break;
				case 1:
					sprite->Play(FLASH_02_ANIMATION);
					break;
				case 2:
					sprite->Play(FLASH_03_ANIMATION);
					break;
				case 3:
					sprite->Play(FLASH_04_ANIMATION);
					break;
			}
			break;
		}

		case MoveState::TURNING_BACKWARD:
			sprite->Play(TURN_BACKWARD_ANIMATION);
			break;

		case MoveState::TAKING_DAMAGE:
			sprite->Play(TAKE_DAMAGE_ANIMATION);
			break;
	}
}

void PlayerRenderingSystem::OnAttackStateChanged()
{
	if (parent.attackState == AttackState::INACTIVE)
		return;

	switch (parent.moveState)
	{
		case MoveState::IDLE:
		case MoveState::WALKING:
			sprite->Play(ATTACK_ANIMATION);
			break;

		case MoveState::IDLE_UPSTAIRS:
			sprite->Play(GO_UPSTAIRS_ATTACK_ANIMATION);
			break;

		case MoveState::IDLE_DOWNSTAIRS:
			sprite->Play(GO_DOWNSTAIRS_ATTACK_ANIMATION);
			break;

		case MoveState::JUMPING:
		case MoveState::HOVERING:
		case MoveState::LANDING:
		case MoveState::FALLING:
			sprite->Play(JUMP_ATTACK_ANIMATION);
			break;

		case MoveState::DUCKING:
			sprite->Play(DUCK_ATTACK_ANIMATION);
			break;
	}
}

void PlayerRenderingSystem::OnUntouchableFinish()
{
	sprite->SetVisibility(true);
}
