#include "PlayerRenderingSystem.h"
#include "PlayerSettings.h"
#include "../../../Settings/Animations.h"

using namespace Castlevania;

constexpr auto BEND_KNEE_ON_JUMPING_Y = 330.0f;
constexpr auto STRETCH_LEG_ON_FALLING_Y = 200.0f;
constexpr auto FLASHING_TIME = 900; // milliseconds

PlayerRenderingSystem::PlayerRenderingSystem(Player &parent, std::string animationPath, std::string flashingAnimationPath) :
	parent{ parent }
{
	this->animationPath = animationPath;
	this->flashingAnimationPath = flashingAnimationPath;
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
	switch (message)
	{
		case MOVE_STATE_CHANGED:
			OnMoveStateChanged();
			break;

		case ATTACK_STATE_CHANGED:
			OnAttackStateChanged();
			break;

		case FACING_CHANGED:
			OnFacingChanged();
			break;
	}
}

void PlayerRenderingSystem::LoadContent(ContentManager &content)
{
	auto animations = content.Load<AnimationFactory>(animationPath);
	auto flashingAnimations = content.Load<AnimationFactory>(flashingAnimationPath);

	sprite = std::make_unique<AnimatedSprite>(animations);
	flashingSprite = std::make_unique<AnimatedSprite>(flashingAnimations);
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

				case MoveState::FLASHING:
					if (flashTimer.ElapsedMilliseconds() >= FLASHING_TIME)
					{
						flashTimer.Reset();

						sprite->GetCurrentAnimation().Continue(); // TODO: make this command actually working
						parent.Idle();
					}
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
	flashingSprite->Update();
}

void PlayerRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	switch (parent.moveState)
	{
		case MoveState::FLASHING:
			spriteBatch.Draw(*flashingSprite, parent.GetPosition());
			break;

		default:
			spriteBatch.Draw(*sprite, parent.GetPosition());
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
			sprite->Play(WALK_ANIMATION);
			// The first frame of WALK_ANIMATION is simon in standing stance, since simon is
			// already standing, if we play 100% of the frame time, it will just sliding at the
			// very first time the simon start to move, we only need to play like 10% once for
			// the standing frame to bootstrap walking animation
			
			// FAQ: Why not just play the second frame?
			//  Because the original game (Castlevania NES) animation seem to work that way
			//  besides of that, if we just barely play the standing frame before actually playing
			//  the walking animation, the transition when simon changes her direction (left|right)
			//  will be smoother (in my personal observation)
			sprite->GetCurrentAnimation().SetElapsedTime(0.9f);
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
			sprite->GetCurrentAnimation().Stop();
			flashTimer.Start();
			auto currentFrameIndex = sprite->GetCurrentAnimation().GetCurrentFrameIndex();

			switch (currentFrameIndex)
			{
				case 0:
					flashingSprite->Play(FLASH_01_ANIMATION);
					break;
				case 1:
					flashingSprite->Play(FLASH_02_ANIMATION);
					break;
				case 2:
					flashingSprite->Play(FLASH_03_ANIMATION);
					break;
				case 3:
					flashingSprite->Play(FLASH_04_ANIMATION);
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
	if (parent.attackState == AttackState::INACTIVE)
		return;

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

void PlayerRenderingSystem::OnFacingChanged()
{
	// Only sprite's SpriteEffects is set by default, make sure to set this too
	if (parent.GetFacing() == Facing::Left)
		flashingSprite->SetEffect(SpriteEffects::FlipHorizontally);
	else
		flashingSprite->SetEffect(SpriteEffects::None);
}
