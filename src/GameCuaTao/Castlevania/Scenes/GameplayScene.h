#pragma once

#include "AbstractScene.h"
#include "Stages/Stage.h"
#include "../Hud.h"

namespace Castlevania
{
	class GameplayScene : public AbstractScene
	{
	public:
		GameplayScene(SceneManager &sceneManager);

		SceneManager &GetSceneManager();
		MapManager &GetMapManager();
		std::shared_ptr<Player> GetPlayer();
		std::shared_ptr<Hud> GetHud();

		void NextStage(Map map);

		void LoadContent() override;
		void Update(GameTime gameTime) override;
		void Draw(GameTime gameTime) override;

	private:
		std::unique_ptr<Stage> currentStage;
		std::unique_ptr<Stage> nextStage;
		std::unique_ptr<MapManager> mapManager;

		std::shared_ptr<Player> player; // Our player need special attention
		std::shared_ptr<Hud> hud;

		std::unique_ptr<Stage> ConstructStage(Map map);
	};
}