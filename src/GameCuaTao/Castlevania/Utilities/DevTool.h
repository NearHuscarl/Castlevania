#pragma once

#include <memory>
#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Extensions/Sprites/Sprite.h"
#include "Direct2DGame/Extensions/Camera.h"
#include "../Models/Factories/ObjectFactory.h"
#include "../Utilities/CollisionGrid.h"
#include "../Utilities/MapSettings.h"

namespace Castlevania
{
	class Stage;

	class DevTool
	{
	public:
		DevTool(Stage &stage);

		static bool IsDebugging;

		void LoadContent(ContentManager &content);
		void Update(UpdateData &updatData);
		void Draw(SpriteExtensions &spriteBatch);

	private:
		using DevToolItems = std::vector<std::pair<std::string, Sprite>>;
		
		std::shared_ptr<SpriteFont> debugFont;

		std::unordered_map<std::string, DevToolItems> items;
		static int currentItemIndex;
		std::string category;
		Facing currentFacing;
		
		std::vector<Map> maps;
		static int currentMapIndex;

		Stage &stage;
		ObjectFactory &objectFactory;
		Player &player;
		Camera &camera;

		std::unique_ptr<EffectFactory> effectFactory;
		std::vector<std::shared_ptr<IEffect>> activeEffects;

		Vector2 GetCurrentItemPosition();
		std::unique_ptr<IEffect> CreateEffect(std::string name);
		void UpdateEffects(GameTime gameTime);
		void DrawCollisionGridInfo(SpriteExtensions &spriteBatch);

		void SetCategory(std::string category);
		void NextItem();
		void PreviousItem();
		
		void SpawnItem();
		void SpawnObject();
		void SpawnEffect();

		void NextMap();
		void PreviousMap();
	};
}