#include "WaterArea.h"
#include "../Settings.h"
#include "../../Utilities/AudioManager.h"

using namespace Castlevania;

WaterArea::WaterArea() : GameObject{ ObjectId::WaterArea }
{
}

void WaterArea::Splash(Vector2 position)
{
	splashPosition = position;
	SendMessageToSystems(OBJECT_HITS_WATER_SURFACE);
	AudioManager::Play(SE_HITTING_WATER_SURFACE);
}
