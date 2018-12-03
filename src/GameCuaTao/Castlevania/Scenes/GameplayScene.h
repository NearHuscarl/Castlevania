#pragma once

#include "AbstractScene.h"
#include "Stages/Stage.h"
#include "GameplayData.h"
#include "../Hud.h"

namespace Castlevania
{
	class GameplayScene : public AbstractScene
	{
	public:
		GameplayScene(SceneManager &sceneManager);

		SceneManager &GetSceneManager();
		MapManager &GetMapManager();
		Sprite &GetCutsceneBackground();

		std::shared_ptr<Player> GetPlayer();
		std::shared_ptr<Hud> GetHud();
		std::shared_ptr<GameplayData> GetData();

		void NextStage(Map map);

		void LoadContent() override;
		void Update(GameTime gameTime) override;
		void Draw(GameTime gameTime) override;

	private:
		std::unique_ptr<Stage> currentStage;
		std::unique_ptr<Stage> nextStage;
		std::unique_ptr<MapManager> mapManager;

		std::unique_ptr<Sprite> cutsceneBackground;
		std::shared_ptr<Player> player; // Our player need special attention
		std::shared_ptr<Hud> hud;
		std::shared_ptr<GameplayData> data;

		std::unique_ptr<Stage> ConstructStage(Map map);
	};
}