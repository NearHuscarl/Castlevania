#include "NextMapCutscene.h"
#include "Stage.h"
#include "StageEvent.h"

using namespace Castlevania;

constexpr auto NEXT_MAP_TRANSITION_TIME = 400; // in milliseconds

NextMapCutscene::NextMapCutscene(Stage &stage, ContentManager &content) : Cutscene{ stage }
{
	auto cutsceneTexture = content.Load<Texture>("Backgrounds/Cutscene_Background.png");
	cutsceneBackground = std::make_unique<Sprite>(cutsceneTexture);

	transitionTimer.Start();
}

void NextMapCutscene::Update(GameTime gameTime)
{
	if (transitionTimer.ElapsedMilliseconds() >= NEXT_MAP_TRANSITION_TIME)
	{
		isComplete = true;
		stage.OnNotify(Subject::Empty(), NEXT_MAP_CUTSCENE_ENDED);
	}
}

void NextMapCutscene::Draw(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(*cutsceneBackground, Vector2::Zero());
}
