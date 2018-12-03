#include "SpawnArea.h"

using namespace Castlevania;

SpawnArea::SpawnArea() : GameObject{ EntityType::SpawnArea }
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
