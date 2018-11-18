#pragma once

#include "Direct2DGame/Utilities/Stopwatch.h"
#include "../../GameObject.h"
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

		// The moment when Simon touch ground after falling from a higher
		// platform, she has to do a superhero landing (DUCK sprite) and
		// wait a moment before changing back into IDLE state. if simon just
		// JUMP and FALL on the same platform, she'd change straight into
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

	class Player : public GameObject
	{
	public:
		Player();

		Facing GetFacing();
		MoveState GetMoveState();
		AttackState GetAttackState();

		void LoadContent(ContentManager &content) override;
		virtual void Update(float deltaTime, ObjectCollection *objectCollection = nullptr) override;
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
		MoveState moveState;
		AttackState attackState;
		Facing facing;
		float jumpSpeed;
		
		Stopwatch jumpCooldown;
		bool isOnGround;

		std::unique_ptr<Whip> whip;

		void SetFacing(Facing facing);

		void Landing(); // Internal command to change from JumpAttacking state to Landing state
		void Land();

		void UpdateStates();
		void UpdateAttackState();

		friend class PlayerResponseSystem;
		friend class PlayerMovementSystem;
	};
}