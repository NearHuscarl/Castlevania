#include "PlayerRenderingSystem.h"
#include "../../Settings.h"
#include "../../../Settings/Animations.h"
#include "../../../Scenes/Stages/StageEvent.h"
#include "../../../Utilities/CppExtensions.h"

using namespace Castlevania;

constexpr auto BEND_KNEE_ON_JUMPING_Y = 330.0f;
constexpr auto STRETCH_LEG_ON_FALLING_Y = 200.0f;

constexpr auto INVISIBLE_EFFECT_START = 2000;
constexpr auto INVISIBLE_EFFECT_END = 4000;

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
		case INVISIBLE_ENDED:
			sprite->SetVisibility(true);
			break;

		case GOD_MODE_ACTIVATED:
		case GOD_MODE_DEACTIVATED:
			PlayAnimation(sprite->GetCurrentAnimation().GetName());
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
			{
				parent.state = ObjectState::DEAD;
				parent.Notify(PLAYER_DIE);
			}
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
						PlayAnimation(JUMP_ANIMATION);

					if (velocity.y > STRETCH_LEG_ON_FALLING_Y)
						PlayAnimation(IDLE_ANIMATION);
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

	if (parent.invisibleTimer.IsRunning())
	{
		UpdateInvisibleRendering();
	}
}

void PlayerRenderingSystem::UpdateInvisibleRendering()
{
	auto invisibleElapsed = parent.invisibleTimer.ElapsedMilliseconds();

	if (invisibleElapsed >= INVISIBLE_EFFECT_START && invisibleElapsed <= INVISIBLE_EFFECT_END)
	{
		if (!drawInvisibleEffect)
		{
			sprite->SetVisibility(true);
			drawInvisibleEffect = true;
			PlayAnimation(sprite->GetCurrentAnimation().GetName());
		}
	}
	else
	{
		if (drawInvisibleEffect)
		{
			drawInvisibleEffect = false;
			PlayAnimation(sprite->GetCurrentAnimation().GetName());
		}

		sprite->SetVisibility(Stopwatch::Every(1) ? true : false);
	}
}

void PlayerRenderingSystem::PlayAnimation(std::string name)
{
	auto animationName = name;
	auto invisibleSuffix = std::string{ "_invisible" };

	if (drawInvisibleEffect || parent.godMode)
	{
		if (!EndsWith(animationName, invisibleSuffix))
			animationName += invisibleSuffix;
	}
	else
	{
		if (EndsWith(animationName, invisibleSuffix))
			animationName = animationName.substr(0, animationName.size() - invisibleSuffix.size());
	}

	if (name == WALK_ANIMATION)
		sprite->PlayCached(animationName);
	else
		sprite->Play(animationName);
}

void PlayerRenderingSystem::OnStateChanged()
{
	switch (parent.state)
	{
		case ObjectState::DYING:
			PlayAnimation(DIE_ANIMATION);
			break;
	}
}

void PlayerRenderingSystem::OnMoveStateChanged()
{
	switch (parent.moveState)
	{
		case MoveState::IDLE:
			PlayAnimation(IDLE_ANIMATION);
			break;

		case MoveState::WALKING:
		case MoveState::WALKING_TO_STAIRS:
			PlayAnimation(WALK_ANIMATION);
			break;

		case MoveState::IDLE_UPSTAIRS:
			PlayAnimation(IDLE_UPSTAIRS_ANIMATION);
			break;

		case MoveState::IDLE_DOWNSTAIRS:
			PlayAnimation(IDLE_DOWNSTAIRS_ANIMATION);
			break;

		case MoveState::GOING_UPSTAIRS:
			PlayAnimation(GO_UPSTAIRS_ANIMATION);
			break;

		case MoveState::GOING_DOWNSTAIRS:
			PlayAnimation(GO_DOWNSTAIRS_ANIMATION);
			break;

		case MoveState::DUCKING:
		case MoveState::LANDING_HARD:
			PlayAnimation(DUCK_ANIMATION);
			break;

		case MoveState::LANDING:
			PlayAnimation(JUMP_ANIMATION);
			break;

		case MoveState::FLASHING:
		{
			auto currentFrameIndex = sprite->GetCurrentAnimation().GetCurrentFrameIndex();

			switch (currentFrameIndex)
			{
				case 0:
					PlayAnimation(FLASH_01_ANIMATION);
					break;
				case 1:
					PlayAnimation(FLASH_02_ANIMATION);
					break;
				case 2:
					PlayAnimation(FLASH_03_ANIMATION);
					break;
				case 3:
					PlayAnimation(FLASH_04_ANIMATION);
					break;
			}
			break;
		}

		case MoveState::TURNING_BACKWARD:
			PlayAnimation(TURN_BACKWARD_ANIMATION);
			break;

		case MoveState::TAKING_DAMAGE:
			PlayAnimation(TAKE_DAMAGE_ANIMATION);
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
			PlayAnimation(ATTACK_ANIMATION);
			break;

		case MoveState::IDLE_UPSTAIRS:
			PlayAnimation(GO_UPSTAIRS_ATTACK_ANIMATION);
			break;

		case MoveState::IDLE_DOWNSTAIRS:
			PlayAnimation(GO_DOWNSTAIRS_ATTACK_ANIMATION);
			break;

		case MoveState::JUMPING:
		case MoveState::HOVERING:
		case MoveState::LANDING:
		case MoveState::FALLING:
			PlayAnimation(JUMP_ATTACK_ANIMATION);
			break;

		case MoveState::DUCKING:
			PlayAnimation(DUCK_ATTACK_ANIMATION);
			break;
	}
}
