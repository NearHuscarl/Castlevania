#pragma once

#include "Direct2DGame/GameTime.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
#include "Direct2DGame/Extensions/Tiled/TiledMap.h"
#include "Direct2DGame/Extensions/Camera.h"
#include "../../Models/Factories/ObjectFactory.h"
#include "../../Utilities/IObserver.h"
#include "../../Utilities/MapManager.h"
#include "../../Hud.h"

namespace Castlevania
{
	class GameplayScene;

	class Stage : public IObserver
	{
	public:
		Stage(GameplayScene &gameplayScene, Map map);

		virtual void OnNotify(Subject &subject, int event) {}

		UpdateData GetUpdateData();

		void Initialize();
		virtual void Update(GameTime gameTime);
		virtual void Draw(SpriteExtensions &spriteBatch);

		virtual ~Stage();

	protected:
		GameplayScene &gameplayScene;
		ObjectFactory &objectFactory;
		Map mapName;

		std::shared_ptr<TiledMap> map;
		std::unique_ptr<Camera> camera;
		std::shared_ptr<Player> player; // Our player need special attention
		std::shared_ptr<Hud> hud;

		ObjectCollection objectCollection; // TODO: move to Grid class (implement spatial partition)

		void LoadMap(Map mapName);
		virtual void UpdateInput();
		void UpdateGameObjects(GameTime gameTime);
		void UpdateGameplay(GameTime gameTime);
	};
}