#pragma once

#include "../GameObject.h"

namespace Castlevania
{
	enum class MoveState
	{
		IDLE,
		WALKING_LEFT,
		WALKING_RIGHT,
		JUMPING,
		JUMPED, // TODO: remove, use collision detection
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

		MoveState GetMoveState();
		AttackState GetAttackState();

		void LoadContent(ContentManager &content) override;
		virtual void Update(float deltaTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

		void Idle();
		void WalkLeft();
		void WalkRight();
		void Jump();
		void Duck();
		void Attack();
		void TurnBackward();

	protected:
		MoveState moveState;
		AttackState attackState;
		Facing facing;
		float jumpSpeed;

		void Attacking();
	};
}