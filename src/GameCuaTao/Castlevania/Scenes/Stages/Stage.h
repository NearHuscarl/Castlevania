#pragma once

#include "Direct2DGame/GameTime.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
#include "Direct2DGame/Extensions/Tiled/TiledMap.h"
#include "Direct2DGame/Extensions/Camera.h"
#include "NextMapCutscene.h"
#include "NextRoomCutscene.h"
#include "GoToCastleCutScene.h"
#include "../../Models/Factories/ObjectFactory.h"
#include "../../Models/Factories/ObjectCollection.h"
#include "../../Utilities/IObserver.h"
#include "../../Utilities/MapSettings.h"
#include "../../Utilities/DevTool.h"
#include "../../Hud.h"

namespace Castlevania
{
	class GameplayScene;

	enum class GameState
	{
		PLAYING,
		NEXT_MAP_CUTSCENE,
		NEXT_ROOM_CUTSCENE,
		GO_TO_CASTLE_CUTSCENE,
	};

	class Stage : public IObserver
	{
	public:
		Stage(GameplayScene &gameplayScene, Map map, std::string checkpoint);

		void OnNotify(Subject &subject, int event);

		Camera *GetCamera();
		UpdateData GetUpdateData();

		void UpdateGameObjects(GameTime gameTime);
		void UpdateGameplay(GameTime gameTime);
		void DrawGameplay(SpriteExtensions &spriteBatch);

		void Initialize();
		void Update(GameTime gameTime);
		void Draw(SpriteExtensions &spriteBatch);

		~Stage();

	private:
		struct StageEvent;

		GameplayScene &gameplayScene;
		ObjectFactory &objectFactory;
		GameState currentState;
		Map currentMap;
		std::string spawnPoint;
		std::unique_ptr<Cutscene> currentCutscene;
		std::unique_ptr<StageEvent> newEvent;

		std::shared_ptr<TiledMap> map;
		std::unique_ptr<Camera> camera;
		std::shared_ptr<Player> player; // Our player need special attention
		std::shared_ptr<Hud> hud;
		std::shared_ptr<GameplayData> data;
		std::unique_ptr<DevTool> devTool;

		ObjectCollection objectCollection; // TODO: move to Grid class (implement spatial partition)

		void SetCurrentCutscene(GameState gameState);
		void LoadObjectsInCurrentArea();
		void LoadMap();

		void OnNextMapCutsceneComplete();
		void OnNextRoomCutsceneComplete();

		void ProcessMessage(int message);

		std::unique_ptr<Cutscene> ConstructCutscene(GameState gameState);
	};
}