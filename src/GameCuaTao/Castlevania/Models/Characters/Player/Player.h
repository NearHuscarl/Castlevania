#pragma once

#include "Direct2DGame/Utilities/Stopwatch.h"
#include "PlayerData.h"
#include "NearbyObjects.h"
#include "../../Weapons/Whip.h"
#include "../../Weapons/RangedWeapon.h"

namespace Castlevania
{
	enum class MoveState
	{
		IDLE,
		WALKING,

		WALKING_TO_STAIRS,
		GOING_UPSTAIRS,
		GOING_DOWNSTAIRS,
		IDLE_UPSTAIRS,
		IDLE_DOWNSTAIRS,

		// From initial jump to when simon reaching HOVERING state
		JUMPING,
		
		// A middleman state between JUMPING and FALLING, simon hovering
		// on the air a little while going to max height, then falling down
		// a bit before changing to FALLING state
		HOVERING,

		// From HOVERING state to when simon hitting ground
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
		
		// Simon freezes and starts flashing after consuming whip-upgrade powerup
		FLASHING,

		DUCKING,
		TURNING_BACKWARD,
		TAKING_DAMAGE
	};

	enum class AttackState
	{
		INACTIVE,
		WHIPPING,
		THROWING,
	};

	class Player : public GameObject
	{
	public:
		Player();

		const PlayerData &GetData();
		const NearbyObjects GetNearbyObjects();
		MoveState GetMoveState();
		AttackState GetAttackState();
		void SetSpeed(float speed) override;
		void SetJumpSpeed(float jumpSpeed);
		void SetFacing(Facing facing) override;
		void AddExp(int amount);
		
		void SetWhip(std::unique_ptr<Whip> whip);
		ObjectId GetSubWeapon();
		void SetSubWeapon(ObjectId weapon);

		void LoadContent(ContentManager &content) override;
		void Update(UpdateData &updateData) override;
		void Draw(SpriteExtensions &spriteBatch) override;

		void Idle();
		void WalkLeft();
		void WalkRight();
		void WalkToStairs();
		void GoUpstairs();
		void GoDownstairs();
		void Jump();
		void Duck();
		void Attack();
		void Throw(std::unique_ptr<RangedWeapon> weapon); // Throw secondary weapon (e.g. dagger, axe, boomerang)
		void TurnBackward();
		void Revive();

		bool IsAttacking();
		bool IsOnTheAir();
		bool IsOnStairs();
		bool CanGoUpstairs();
		bool CanGoDownstairs();

	private:
		PlayerData data;
		MoveState moveState;
		AttackState attackState;
		float stairWalkingSpeed;
		float jumpSpeed;

		std::unique_ptr<Whip> whip;
		std::unique_ptr<RangedWeapon> subWeapon;

		void SetMoveState(MoveState moveState);
		void SetAttackState(AttackState attackState);

		void IdleOnGround();
		void DoThrow(); // finish throwing maneuver, weapon is now launching
		void Fall();
		void Land();
		void Flash(); // simon flashing when getting whip-upgrade powerup
		void TakeDamage(int damage, Direction direction);
		void BounceBack(Direction direction); // when simon taking damage
		void Die();

		void UpdateStates();
		void UpdateSubWeapons(UpdateData &updateData);
		void OnAttackComplete();
		void OnHitStairEntry();

		friend class PlayerResponseSystem;
		friend class PlayerMovementSystem;
		friend class PlayerRenderingSystem;
		friend class DevTool;

		Stopwatch landingTimer;
		Stopwatch flashingTimer;
		Stopwatch untouchableTimer; // cooldown time after taking damage

		// Component-related flags
		NearbyObjects nearbyObjects;
	};
}