#include "Cutscene.h"
#include "Stage.h"

using namespace Castlevania;

Cutscene::Cutscene(Stage &stage) : stage{ stage }
{
	isComplete = false;
}

bool Cutscene::IsComplete()
{
	return isComplete;
}

void Cutscene::Draw(SpriteExtensions &spriteBatch)
{
	stage.DrawGameplay(spriteBatch);
}
