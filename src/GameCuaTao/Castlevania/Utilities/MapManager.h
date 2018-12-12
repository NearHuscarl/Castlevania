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
	using GameObjects = std::vector<std::unique_ptr<GameObject>>;

	class MapManager
	{
	public:
		MapManager(ObjectFactory &objectFactory);

		void SetWorldPosition(Vector2 position);

		void LoadContent(ContentManager &content);

		std::shared_ptr<TiledMap> GetTiledMap(Map name);
		
		ObjectCollection GetOtherObjects(Map name); // Get all other objects except object in ENITY type
		GameObjects GetMapObjects(Map name);
		GameObjects GetMapObjectsInArea(Map name, Rect area);

	private:
		Maps maps;

		Vector2 worldPosition; // absolute position of map and map objects to the world
		ObjectFactory &objectFactory;

		// Create game objects within an area
		ObjectCollection CreateObjectCollection(TiledMapObjectGroups objectGroups);
		std::unique_ptr<GameObject> ConstructObject(ObjectProperties properties);
		
		void ReadObjectPosition(ObjectProperties properties, float &x, float &y);
	};
}