#pragma once

#include "Direct2DGame/Content/ContentManager.h"
#include "Models/Characters/Player/PlayerData.h"
#include "Scenes/GameplayData.h"

namespace Castlevania
{
	// Head-up display to show current player stats (health, weapon...)
	// on top of the screen
	class Hud
	{
	public:
		Hud(GraphicsDevice &graphicsDevice);

		int GetWidth();
		int GetHeight();

		void Register(const PlayerData &playerData);
		void Register(const int &bossHealth);
		void Register(const GameplayData &gameplayData);

		template<typename T>
		void Unregister();

		void LoadContent(ContentManager &content);
		void Draw(SpriteExtensions &spriteBatch);

		~Hud();

	private:
		struct HudData;

		std::unique_ptr<HudData> data;

		int width;
		int height;

		std::shared_ptr<SpriteFont> hudFont;
		std::shared_ptr<Texture> backgroundTexture;
		std::shared_ptr<Texture> borderTexture;
		std::shared_ptr<Texture> heartTexture;

		std::shared_ptr<Texture> axeItemTexture;
		std::shared_ptr<Texture> daggerItemTexture;
		std::shared_ptr<Texture> holyWaterItemTexture;

		std::unique_ptr<Sprite> playerFullBlock;
		std::unique_ptr<Sprite> bossFullBlock;
		std::unique_ptr<Sprite> emptyBlock;

		Vector2 scoreTextPosition;
		Vector2 timeTextPosition;
		Vector2 stageTextPosition;
		Vector2 playerTextPosition;
		Vector2 playerHealthPosition;
		Vector2 enemyTextPosition;
		Vector2 enemyHealthPosition;
		Vector2 borderTexturePosition;
		Vector2 heartTexturePosition;
		Vector2 heartTextPosition;
		Vector2 liveTextPosition;

		std::string GetScoreText();
		std::string GetTimeText();
		std::string GetStageText();
		std::string GetHeartCountText();
		std::string GetLiveCountText();

		std::shared_ptr<Texture> GetWeaponTexture();
		Vector2 GetWeaponPosition(Texture &weaponTexture);
		void DrawHealthBars(SpriteExtensions &spriteBatch);

		std::string padZero(int number, int paddingCount); // (123, 5) -> "00123"
	};
}