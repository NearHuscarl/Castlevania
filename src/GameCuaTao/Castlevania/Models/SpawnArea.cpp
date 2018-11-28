#include "SpawnArea.h"

using namespace Castlevania;

SpawnArea::SpawnArea(RectF boundingBox) : RectangleObject{ boundingBox, EntityType::SpawnArea }
{
}

void SpawnArea::SetActive(bool value)
{
	isActive = value;
}

void SpawnArea::Update(GameTime gameTime)
{
}

//void SpawnArea::Draw(GameTime gameTime)
//{
//}
