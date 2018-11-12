#pragma once

#include "Direct2DGame/Extensions/Tiled/TiledMap.h"
#include "../Factories/ObjectFactory.h"

namespace Castlevania
{
	// https://www.castle.lv/castles4/hroniki/glossary.html
	enum class Map
	{
		INTRO,
		STAGE_01_COURTYARD,
		STAGE_01_GREAT_HALL,
		STAGE_01_UNDERGROUND,
	};

	using Maps = std::map<Map, std::shared_ptr<TiledMap>>;

	class StageManager
	{
	public:
		void LoadContent(ContentManager &content);
		std::shared_ptr<TiledMap> NextMap(Map name);
		ObjectCollection LoadGameObjects();

	private:
		Maps maps;
		std::shared_ptr<TiledMap> currentMap;
		ObjectFactory objectFactory;
	};
}