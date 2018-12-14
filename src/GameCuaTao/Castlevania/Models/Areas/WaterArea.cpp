#include "WaterArea.h"

using namespace Castlevania;

WaterArea::WaterArea(EffectFactory &effectFactory) :
	GameObject{ EntityType::WaterArea },
	effectFactory{ effectFactory }
{
}

void WaterArea::SpawnWaterEffect(Vector2 position)
{
}
