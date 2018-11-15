#pragma once

#include "../GameObject.h"
#include "../Weapons/Whip.h"

namespace Castlevania
{
	enum class MoveState
	{
		IDLE,
		WALKING,
		JUMPING,
		JUMPED, // TODO: remove, use collision detection
		
		// Simon bends her knee after attacking on the air. Normally she
		// would stretch her leg on her way down if she is in IDLE state
		LANDING,
		DUCKING,
		TURNING_BACKWARD,
	};

	enum class AttackState
	{
		INACTIVE,
		ATTACKING,
	};

	class Simon : public GameObject
	{
	public:
		Simon(EntityType type = EntityType::Simon);

		void SetFacing(Facing facing);
		Facing GetFacing();
		MoveState GetMoveState();
		AttackState GetAttackState();

		void LoadContent(ContentManager &content) override;
		virtual void Update(float deltaTime, ObjectCollection *objectCollection = nullptr) override;
		void Draw(SpriteExtensions &spriteBatch) override;

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

		std::unique_ptr<Whip> whip;

		void Land(); // Internal command to change from JumpAttacking state to Landing state
		void UpdateJumpState();
		void UpdateAttackState();
	};
}