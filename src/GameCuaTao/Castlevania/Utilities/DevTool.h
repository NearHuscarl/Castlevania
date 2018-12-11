#pragma once

#include <memory>
#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Extensions/Sprites/Sprite.h"
#include "Direct2DGame/Extensions/Camera.h"
#include "../Models/Factories/ObjectCollection.h"
#include "../Models/Factories/ObjectFactory.h"
#include "../Utilities/MapSettings.h"

namespace Castlevania
{
	class GameplayScene;

	class DevTool
	{
	public:
		DevTool(GameplayScene &gameplayScene, Camera &camera);

		void LoadContent(ContentManager &content);
		void Update(ObjectCollection &objectCollection);
		void Draw(SpriteExtensions &spriteBatch);

	private:
		using DevToolItems = std::vector<std::pair<std::string, Sprite>>;
		
		bool isDebugging;
		std::shared_ptr<SpriteFont> debugFont;

		std::unordered_map<std::string, DevToolItems> items;
		static int currentItemIndex;
		std::string category;
		Facing currentFacing;
		
		std::vector<Map> maps;
		static int currentMapIndex;

		GameplayScene &gameplayScene;
		ObjectFactory &objectFactory;
		Camera &camera;

		Vector2 GetCurrentItemPosition();

		void SetCategory(std::string category);
		void NextItem();
		void PreviousItem();
		void SpawnItem(ObjectCollection &objectCollection);

		void NextMap();
		void PreviousMap();
	};
}