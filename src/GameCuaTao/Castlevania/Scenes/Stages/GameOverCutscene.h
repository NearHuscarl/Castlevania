#pragma once

#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Utilities/Stopwatch.h"
#include "Cutscene.h"

namespace Castlevania
{
	class GameplayScene;

	class GameOverCutscene : public Cutscene
	{
	public:
		GameOverCutscene(Stage &stage, ContentManager &content, GameplayScene &gameplayScene);

		void Update(UpdateData &updateData) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		enum class State;

		GameplayScene &gameplayScene;
		std::unique_ptr<Sprite> cutsceneBackground;
		Stopwatch transitionTimer;
		State currentState;
	};
}