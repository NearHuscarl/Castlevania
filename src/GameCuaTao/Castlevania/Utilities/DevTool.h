#pragma once

#include <memory>
#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Extensions/Sprites/Sprite.h"
#include "Direct2DGame/Extensions/Camera.h"
#include "../Models/Factories/ObjectCollection.h"
#include "../Models/Factories/ObjectFactory.h"

namespace Castlevania
{
	class DevTool
	{
	public:
		DevTool(ObjectFactory &objectFactory, Camera &camera);

		void LoadContent(ContentManager &content);
		void Update(ObjectCollection &objectCollection);
		void Draw(SpriteExtensions &spriteBatch);

	private:
		using DevToolItems = std::vector<std::pair<std::string, Sprite>>;

		std::shared_ptr<SpriteFont> debugFont;
		DevToolItems items;
		int currentItemIndex;
		Facing currentFacing;

		ObjectFactory &objectFactory;
		Camera &camera;

		//std::unique_ptr<GameObject> SpawnItem(EntityType type);
	};
}