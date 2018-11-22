#include "PlayerRenderingSystem.h"
#include "PlayerSettings.h"
#include "../../../Settings/Animations.h"

using namespace Castlevania;

constexpr auto BEND_KNEE_ON_JUMPING_Y = 330.0f;
constexpr auto STRETCH_LEG_ON_FALLING_Y = 200.0f;

PlayerRenderingSystem::PlayerRenderingSystem(Player &parent, std::string spriteConfigPath) :
	parent{ parent }
{
	this->spriteConfigPath = spriteConfigPath;
}

RectF PlayerRenderingSystem::GetBoundingBox()
{
	return sprite->GetBoundingRectangle(parent.GetPosition());
}

Sprite &PlayerRenderingSystem::GetSprite()
{
	return *sprite;
}

void PlayerRenderingSystem::Receive(int message)
{
	if (message == MOVE_STATE_CHANGED)
	{
		OnMoveStateChanged();
	}
	else if (message == ATTACK_STATE_CHANGED)
	{
		OnAttackStateChanged();
	}
}

void PlayerRenderingSystem::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>(spriteConfigPath);
	sprite = std::make_unique<AnimatedSprite>(animationFactory);
}

void PlayerRenderingSystem::Update(float deltaTime)
{
	auto moveState = parent.GetMoveState();
	auto attackState = parent.GetAttackState();
	auto velocity = parent.GetVelocity();

	switch (attackState)
	{
		case AttackState::INACTIVE:
			switch (moveState)
			{
				case MoveState::JUMPING:
					if (velocity.y > -BEND_KNEE_ON_JUMPING_Y)
						sprite->Play(JUMP_ANIMATION);
					break;

				case MoveState::FALLING:
				case MoveState::LANDING:
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
			{
				parent.OnAttackComplete();

				switch (moveState)
				{
					case MoveState::WALKING:
					case MoveState::IDLE:
						sprite->Play(IDLE_ANIMATION);
						break;

					case MoveState::JUMPING:
					case MoveState::FALLING:
						sprite->Play(JUMP_ANIMATION);
						break;

					case MoveState::DUCKING:
						sprite->Play(DUCK_ANIMATION);
						break;
				}
			}
			break;
	}

	sprite->Update();
}

void PlayerRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(*sprite, parent.GetPosition());
}

void PlayerRenderingSystem::OnMoveStateChanged()
{
	switch (parent.moveState)
	{
		case MoveState::IDLE:
			sprite->Play(IDLE_ANIMATION);
			break;

		case MoveState::WALKING:
			sprite->Play(WALK_ANIMATION);
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
	}
}

void PlayerRenderingSystem::OnAttackStateChanged()
{
	if (parent.attackState == AttackState::WHIPPING
		|| parent.attackState == AttackState::THROWING)
	{
		switch (parent.moveState)
		{
			case MoveState::WALKING:
				sprite->Play(ATTACK_ANIMATION);
				break;

			case MoveState::IDLE:
				sprite->Play(ATTACK_ANIMATION);
				break;

			case MoveState::JUMPING:
			case MoveState::LANDING:
			case MoveState::FALLING:
				sprite->Play(JUMP_ATTACK_ANIMATION);
				break;

			case MoveState::DUCKING:
				sprite->Play(DUCK_ATTACK_ANIMATION);
				break;
		}
	}
}
