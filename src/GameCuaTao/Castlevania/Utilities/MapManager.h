#pragma once

#include "Direct2DGame/Extensions/Tiled/TiledMap.h"
#include "MapSettings.h"
#include "../Models/Factories/ObjectFactory.h"
#include "../Models/Factories/ObjectCollection.h"
#include "../Scenes/Stages/StageObject.h"

namespace Castlevania
{
	using Maps = std::map<Map, std::shared_ptr<TiledMap>>;
	using ObjectProperties = std::unordered_map<std::string, std::string>;
	using ObjectsProperties = std::vector<ObjectProperties>;
	
	enum class MapObjectType
	{
		Tile,
		Rectangle,
	};

	class MapManager
	{
	public:
		MapManager(ObjectFactory &objectFactory);

		void LoadContent(ContentManager &content);

		void SetWorldPosition(Vector2 position);
		std::shared_ptr<TiledMap> GetTiledMap(Map name);
		std::unique_ptr<StageObject> GetStageObjects(Map name);
		ObjectCollection GetMapObjects(Map name);
		ObjectCollection GetMapObjectsInArea(Map name, RectF area);

	private:
		Maps maps;

		Vector2 worldPosition; // absolute position of map and map objects to the world
		ObjectFactory &objectFactory;

		std::unique_ptr<GameObject> ConstructObject(ObjectProperties properties);
		RectF GetMapObjectBoundingBox(ObjectProperties properties, MapObjectType type);
	};
}