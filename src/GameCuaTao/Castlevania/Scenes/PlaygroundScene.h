#pragma once

#include "AbstractScene.h"
#include "Direct2DGame/Extensions/Tiled/TiledMap.h"
#include "Direct2DGame/Extensions/Camera.h"
#include "../Utilities/StageManager.h"
#include "../Hud.h"

namespace Castlevania
{
	// For testing purpose
	class PlaygroundScene : public AbstractScene
	{
	public:
		PlaygroundScene(SceneManager &sceneManager, ObjectFactory &objectFactory);

		void LoadContent() override;
		void Update(float deltaTime) override;
		void Draw(GameTime gameTime) override;

	private:
		ObjectFactory &objectFactory;

		std::unique_ptr<StageManager> stageManager;
		std::shared_ptr<TiledMap> map;
		std::unique_ptr<Camera> camera;
		std::unique_ptr<Player> player; // Our player need special attention
		std::unique_ptr<Hud> hud;

		ObjectCollection objectCollection; // TODO: move to Grid class (implement spatial partition)
	};
}