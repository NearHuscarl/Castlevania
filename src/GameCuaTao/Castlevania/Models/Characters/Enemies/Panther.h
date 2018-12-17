#pragma once

#include "Enemy.h"

namespace Castlevania
{
	enum class PantherState
	{
		IDLE,
		RUNNING,
		JUMPING,
	};

	class Panther : public Enemy
	{
	public:
		Panther();

		// If Simon steps into the active area
		// Switch to active mode and start chasing her
		RectF GetActiveZone();
		void SetActiveZone(Rect activeZone);
		void SetJumpSpeed(float speed);
		
		bool IsActive();
		void SetActive(bool value);

		PantherState GetPantherState();
		Direction GetPlayerDirection();

		void Update(GameTime gameTime, UpdateData &updateData) override;

		void Idle();
		void RunRight();
		void RunLeft();
		void Jump();
		void Land();

	private:
		float jumpSpeed;
		bool isActive;
		Rect activeZone;
		PantherState pantherState;
		Direction playerDirection;

		void SetPantherState(PantherState state);
	};
}