#pragma once

#include "Direct2DGame/Content/ContentManager.h"
#include "Models/Characters/Player/PlayerData.h"

namespace Castlevania
{
	// Head-up display to show current player stats (health, weapon...)
	// on top of the screen
	class Hud
	{
	public:
		Hud(const PlayerData &data);

		void LoadContent(ContentManager &content);
		void Draw(SpriteExtensions &spriteBatch);

	private:
		const PlayerData &data;

		std::shared_ptr<SpriteFont> hudFont;
		std::shared_ptr<Texture> borderTexture;
		std::shared_ptr<Texture> heartTexture;

		std::string GetScoreText();
		std::string GetTimeText();
		std::string GetStageText();
		std::string GetHeartText();
		std::string GetPText(); // TODO

		Vector2 scoreTextPosition;
		Vector2 timeTextPosition;
		Vector2 stageTextPosition;
		Vector2 playerTextPosition;
		Vector2 enemyTextPosition;
		Vector2 borderTexturePosition;
		Vector2 heartTexturePosition;
		Vector2 heartTextPosition;

		std::string padZero(int number, int paddingCount); // (123, 5) -> "00123"
	};
}