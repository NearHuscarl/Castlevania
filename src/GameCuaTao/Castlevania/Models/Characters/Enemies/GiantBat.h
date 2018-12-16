#pragma once

#include "Direct2DGame/Utilities/Stopwatch.h"
#include "Enemy.h"
#include "../../IBoss.h"

namespace Castlevania
{
	enum class GiantBatState
	{
		IDLE,
		HOVERING,
		FLYING,
		DIVING,
		SHOOTING,
	};

	class GiantBat : public Enemy, public IBoss
	{
	public:
		GiantBat();

		void SetDiveSpeed(float speed);
		void SetActive() override;
		bool IsInRange();
		void IsInRange(bool value);

		Rect GetAttackArea();
		void SetAttackZone(Rect attackZone);
		GiantBatState GetGiantBatState();

		void Idle();
		void Hover();
		void FlyTo(Vector2 position);
		void Dive(Vector2 vertex);
		void Shoot(std::unique_ptr<GameObject> fireball);

	private:
		Vector2 destination;
		float diveSpeed;
		bool isInRange;
		Rect attackZone;
		GiantBatState giantBatState;

		void SetGiantBatState(GiantBatState state);

		friend class GiantBatMovementSystem;
	};
}