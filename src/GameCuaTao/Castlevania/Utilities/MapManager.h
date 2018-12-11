#pragma once

#include "Direct2DGame/Extensions/Tiled/TiledMap.h"
#include "MapSettings.h"
#include "../Models/Factories/ObjectFactory.h"
#include "../Models/Factories/ObjectCollection.h"

namespace Castlevania
{
	using Maps = std::map<Map, std::shared_ptr<TiledMap>>;

	using ObjectProperties = std::unordered_map<std::string, std::string>;
	using ObjectsProperties = std::vector<ObjectProperties>;

	struct MapData
	{
		std::shared_ptr<TiledMap> map;
		ObjectCollection objects;
	};

	class MapManager
	{
	public:
		MapManager(ObjectFactory &objectFactory);

		void SetWorldPosition(Vector2 position);

		void LoadContent(ContentManager &content);
		MapData LoadMap(Map name);
		void GetViewportAreas(Map name, std::vector<std::unique_ptr<GameObject>> &viewportAreas);

	private:
		Maps maps;

		Vector2 worldPosition; // absolute position of map and map objects to the world
		ObjectFactory &objectFactory;

		ObjectCollection CreateObjectCollection(TiledMapObjectGroups objectGroups);
		std::unique_ptr<GameObject> ConstructObject(ObjectProperties properties);
		std::unique_ptr<GameObject> ConstructArea(ObjectProperties properties);
		
		void ReadObjectPosition(ObjectProperties properties, float &x, float &y);
	};
}