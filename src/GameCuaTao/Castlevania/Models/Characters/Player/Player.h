#pragma once

#include "Direct2DGame/Utilities/Stopwatch.h"
#include "PlayerData.h"
#include "../../Weapons/Whip.h"

namespace Castlevania
{
	enum class MoveState
	{
		IDLE,
		WALKING,

		// From initial jump to when simon reaching max height
		JUMPING,
		
		// After simon reaching max height to when simon hitting ground
		FALLING,
		
		// Like FALLING but happen when simon walk and fall from a higher
		// platform (without JUMPING). She falls down way faster compared
		// to when in FALLING state. When touching ground, simon will move
		// into LANDING_HARD state instead of IDLE
		FALLING_HARD,

		// Simon bends her knee after performing a jump attack. Normally she
		// would stretch her leg on her way down if she is not attacking
		// mid-air
		LANDING,

		// The moment when Simon touches ground after falling from a higher
		// platform, she has to do a superhero landing (DUCK sprite) and
		// wait a moment before changing back into IDLE state. if simon just
		// JUMPes and FALLs on the same platform, she'd change straight into
		// IDLE state after touching the ground
		LANDING_HARD,
		
		DUCKING,
		TURNING_BACKWARD,
	};

	enum class AttackState
	{
		INACTIVE,
		ATTACKING,
	};

	class Player : public AnimatedObject
	{
	public:
		Player();

		const PlayerData &GetData();
		void SetWhip(std::unique_ptr<Whip> whip);
		MoveState GetMoveState();
		AttackState GetAttackState();

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime, ObjectCollection *objectCollection = nullptr) override;
		void Draw(SpriteExtensions &spriteBatch) override;
		void DrawBoundingBox(SpriteExtensions &spriteBatch) override;

		void Idle();
		void WalkLeft();
		void WalkRight();
		void Jump();
		void Duck();
		void Attack();
		void TurnBackward();

	private:
		PlayerData data;
		MoveState moveState;
		AttackState attackState;
		float jumpSpeed;
		
		Stopwatch jumpCooldown;
		bool isOnGround;

		std::unique_ptr<Whip> whip;

		void SetFacing(Facing facing);

		void Landing(); // Internal command to change from JumpAttacking state to Landing state
		void Land();

		void UpdateStates(float deltaTime);
		void UpdateAttackState();

		friend class PlayerResponseSystem;
		friend class PlayerMovementSystem;
	};
}