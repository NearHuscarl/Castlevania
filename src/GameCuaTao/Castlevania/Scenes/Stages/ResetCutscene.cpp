#include "ResetCutscene.h"
#include "Stage.h"
#include "StageEvent.h"

using namespace Castlevania;

enum class ResetCutscene::State
{
	BEFORE_PLAYING_CUTSCENE,
	PLAYING_CUTSCENE,
};

constexpr auto TRANSITION_WAITING_TIME = 1200; // in milliseconds
constexpr auto RESET_TRANSITION_TIME = 400; // in milliseconds

ResetCutscene::ResetCutscene(Stage &stage, ContentManager &content) : Cutscene{ stage }
{
	auto cutsceneTexture = content.Load<Texture>("Backgrounds/Cutscene_Background.png");
	cutsceneBackground = std::make_unique<Sprite>(cutsceneTexture);
	currentState = State::BEFORE_PLAYING_CUTSCENE;

	stage.GetHud()->Unregister<int>(); // unregister boss health if in boss scene
	transitionTimer.Start();
}

void ResetCutscene::Update(UpdateData &updateData)
{
	stage.UpdateGameplay(updateData);

	switch (currentState)
	{
		case State::BEFORE_PLAYING_CUTSCENE:
			if (transitionTimer.ElapsedMilliseconds() >= TRANSITION_WAITING_TIME)
			{
				transitionTimer.Restart();
				currentState = State::PLAYING_CUTSCENE;
			}
			break;

		case State::PLAYING_CUTSCENE:
			if (transitionTimer.ElapsedMilliseconds() >= RESET_TRANSITION_TIME)
				isComplete = true;
			break;
	}
}

void ResetCutscene::Draw(SpriteExtensions &spriteBatch)
{
	if (currentState == State::PLAYING_CUTSCENE)
		spriteBatch.Draw(*cutsceneBackground, Vector2::Zero(), false);
	else
		Cutscene::Draw(spriteBatch);

	if (isComplete)
		stage.OnNotify(Subject::Empty(), RESET_STAGE_CUTSCENE_ENDED);
}
