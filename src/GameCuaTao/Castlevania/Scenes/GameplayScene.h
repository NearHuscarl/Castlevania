#pragma once

#include "AbstractScene.h"
#include "Direct2DGame/Extensions/Tiled/TiledMap.h"

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
		std::shared_ptr<TiledMap> tiledMap;
	};
}