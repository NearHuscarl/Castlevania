#include "ResetCutscene.h"
#include "Stage.h"
#include "StageEvent.h"

using namespace Castlevania;

constexpr auto RESET_TRANSITION_TIME = 400; // in milliseconds

ResetCutscene::ResetCutscene(Stage &stage, ContentManager &content) : Cutscene{ stage }
{
	auto cutsceneTexture = content.Load<Texture>("Backgrounds/Cutscene_Background.png");
	cutsceneBackground = std::make_unique<Sprite>(cutsceneTexture);

	stage.GetHud()->Unregister<int>(); // unregister boss health if in boss scene
	transitionTimer.Start();
}

void ResetCutscene::Update(UpdateData &updateData)
{
	if (transitionTimer.ElapsedMilliseconds() >= RESET_TRANSITION_TIME)
	{
		isComplete = true;
	}
}

void ResetCutscene::Draw(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(*cutsceneBackground, Vector2::Zero());

	if (isComplete)
		stage.OnNotify(Subject::Empty(), RESET_STAGE_CUTSCENE_ENDED);
}
