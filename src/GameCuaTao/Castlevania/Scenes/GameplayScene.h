#pragma once

#include "AbstractScene.h"
#include "Direct2DGame/Extensions/Tiled/TiledMap.h"
#include "Direct2DGame/Extensions/Camera.h"
#include "../Utilities/MapManager.h"
#include "../Hud.h"

namespace Castlevania
{
	enum class GameState
	{
		PLAYING,
		NEXT_ROOM_TRANSITION,
		GO_TO_CASTLE_TRANSITION,
	};

	class GameplayScene : public AbstractScene
	{
	public:
		GameplayScene(SceneManager &sceneManager, ObjectFactory &objectFactory);

		void LoadContent() override;
		void Update(GameTime gameTime) override;
		void Draw(GameTime gameTime) override;

	private:
		GameState gameState;
		ObjectFactory &objectFactory;

		std::unique_ptr<MapManager> mapManager;
		std::shared_ptr<TiledMap> map;
		std::unique_ptr<Camera> camera;
		std::unique_ptr<Player> player; // Our player need special attention
		std::unique_ptr<Hud> hud;

		ObjectCollection objectCollection; // TODO: move to Grid class (implement spatial partition)

		UpdateData updateData;

		void LoadMap(Map mapName);
		void UpdateInput();
		void UpdateGameplay(GameTime gameTime);
	};
}