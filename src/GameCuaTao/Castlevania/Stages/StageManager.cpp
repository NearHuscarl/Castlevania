#include "StageManager.h"

using namespace Castlevania;

void StageManager::LoadContent(ContentManager &content)
{
	//maps[Map::INTRO] = content.Load<TiledMap>("TiledMaps/Intro.tmx");
	maps[Map::STAGE_01_COURTYARD] = content.Load<TiledMap>("TiledMaps/Stage_01/Courtyard.tmx");
	//maps[Map::STAGE_01_GREAT_HALL] = content.Load<TiledMap>("TiledMaps/Stage_01/Great_Hall.tmx");
	//maps[Map::STAGE_01_UNDERGROUND] = content.Load<TiledMap>("TiledMaps/Stage_01/Underground.tmx");
}

std::shared_ptr<TiledMap> StageManager::NextMap(Map name)
{
	currentMap = maps.at(name);
	return currentMap;
}

GameObjects StageManager::LoadGameObjects()
{
	auto mapObjects = currentMap->GetMapObjects();
	auto gameObjects = GameObjects{};

	for (auto mapObject : mapObjects)
	{
		gameObjects.push_back(objectFactory.CreateObject(mapObject));
	}

	return gameObjects;
}
