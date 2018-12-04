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

		bool IsActive();
		void SetActive(bool value);

		// If Simon steps into the active area
		// Switch to active mode and start chasing her
		RectF GetActiveArea();
		PantherState GetPantherState();
		Direction GetPlayerDirection();

		void Update(GameTime gameTime, UpdateData &updateData) override;

		void Idle();
		void RunRight();
		void RunLeft();
		void Jump();
		void Land();

	private:
		bool isActive;
		Rect activeArea;
		PantherState pantherState;
		Direction playerDirection;

		void SetPantherState(PantherState state);
		
		friend class PantherCollisionSystem;
	};
}