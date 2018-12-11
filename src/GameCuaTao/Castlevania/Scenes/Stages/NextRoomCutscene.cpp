#include "NextRoomCutscene.h"

using namespace Castlevania;

NextRoomCutscene::NextRoomCutscene(Player &player, Camera &camera, Door &door) :
	player{ player },
	camera{ camera },
	door{ door }
{
}

void NextRoomCutscene::Update(GameTime gameTime)
{
}
