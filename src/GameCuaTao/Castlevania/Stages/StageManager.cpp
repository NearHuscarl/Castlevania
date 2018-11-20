#include "StageManager.h"

using namespace Castlevania;

StageManager::StageManager(ObjectFactory &objectFactory) : objectFactory{ objectFactory }
{
}

void StageManager::LoadContent(ContentManager &content)
{
	//maps[Map::INTRO] = content.Load<TiledMap>("TiledMaps/Intro.tmx");
	maps[Map::STAGE_01_COURTYARD] = content.Load<TiledMap>("TiledMaps/Stage_01/Courtyard.tmx");
	//maps[Map::STAGE_01_GREAT_HALL] = content.Load<TiledMap>("TiledMaps/Stage_01/Great_Hall.tmx");
	//maps[Map::STAGE_01_UNDERGROUND] = content.Load<TiledMap>("TiledMaps/Stage_01/Underground.tmx");
	maps[Map::PLAYGROUND] = content.Load<TiledMap>("TiledMaps/Playground/Playground.tmx");
}

std::shared_ptr<TiledMap> StageManager::NextMap(Map name)
{
	currentMap = maps.at(name);

	return currentMap;
}

ObjectCollection StageManager::LoadGameObjects()
{
	auto mapObjects = currentMap->GetMapObjects();

	return objectFactory.CreateObjectCollection(mapObjects);
}
