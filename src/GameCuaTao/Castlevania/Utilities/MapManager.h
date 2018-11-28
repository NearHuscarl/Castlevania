#pragma once

#include "Direct2DGame/Extensions/Tiled/TiledMap.h"
#include "../Models/Factories/ObjectFactory.h"
#include "../Models/Factories/ObjectCollection.h"

namespace Castlevania
{
	enum class Map
	{
		INTRO,
		COURTYARD,
		GREAT_HALL,
		UNDERGROUND,
		PLAYGROUND,
	};

	using Maps = std::map<Map, std::shared_ptr<TiledMap>>;

	using ObjectProperties = std::map<std::string, std::string>;
	using ObjectsProperties = std::vector<ObjectProperties>;

	class MapManager
	{
	public:
		MapManager(ObjectFactory &objectFactory);

		Map GetCurrentMap();
		void SetWorldPosition(Vector2 position);

		void LoadContent(ContentManager &content);
		std::shared_ptr<TiledMap> NextMap(Map name);
		ObjectCollection LoadGameObjects();

	private:
		Maps maps;
		Map currentMap;

		Vector2 worldPosition; // absolute position of map and map objects to the world
		ObjectFactory &objectFactory;

		ObjectCollection CreateObjectCollection(ObjectsProperties properties);
		std::unique_ptr<GameObject> ConstructObject(ObjectProperties properties);
	};
}