#pragma once

#include "GameObject.h"

namespace Castlevania
{
	enum class Facing
	{
		Left,
		Right
	};

	class Simon : public GameObject
	{
	public:
		void LoadContent(ContentManager &content) override;
		virtual void Update(float deltaTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

		// TODO: make an IntroController, those should be in private
		void Idle();
		void WalkLeft();
		void WalkRight();
		void TurnBackward();

	protected:
		enum class State
		{
			WALKING_LEFT,
			WALKING_RIGHT,
			IDLE,
			TURNING_BACKWARD,
		};

		State state;
		Facing facing;

		void SetFacing(Facing facing);
	};
}