#include "WaterArea.h"
#include "../Settings.h"

using namespace Castlevania;

WaterArea::WaterArea() : GameObject{ EntityType::WaterArea }
{
}

void WaterArea::Splash(Vector2 position)
{
	splashPosition = position;
	SendMessageToSystems(OBJECT_HITS_WATER_SURFACE);
}
