#pragma once

#include "AbstractScene.h"
#include "Direct2DGame/Extensions/Tiled/TiledMap.h"
#include "Direct2DGame/Extensions/Camera.h"
#include "../Models/GameObject.h"
#include "../Stages/StageManager.h"

namespace Castlevania
{
	class GameplayScene : public AbstractScene
	{
	public:
		GameplayScene(SceneManager &sceneManager);

		void LoadContent() override;
		void Update(float deltaTime) override;
		void Draw(GameTime gameTime) override;

	private:
		std::unique_ptr<StageManager> stageManager;
		std::shared_ptr<TiledMap> map;
		std::unique_ptr<Camera> camera;
		std::unique_ptr<Player> player; // Our player need special attention

		ObjectFactory objectFactory;
		ObjectCollection objectCollection; // TODO: move to Grid class (implement spatial partition)
	};
}