#include <iomanip>
#include <sstream>
#include "Hud.h"

using namespace Castlevania;

Hud::Hud(const PlayerData &data) : data{ data }
{
	scoreTextPosition = Vector2{ 0, 15 };
	timeTextPosition = Vector2{ 210, 15 };
	stageTextPosition = Vector2{ 370, 15 };
	playerTextPosition = Vector2{ 0, 32 };
	playerHealthPosition = Vector2{ 105, 33 };
	enemyTextPosition = Vector2{ 2, 49 };
	enemyHealthPosition = Vector2{ 105, 49 };
	borderTexturePosition = Vector2{ 260, 32 };
	heartTexturePosition = Vector2{ 340, 32 };
	heartTextPosition = Vector2{ 355, 32 };
	liveTextPosition = Vector2{ 340, 49 };
}

void Hud::LoadContent(ContentManager &content)
{
	hudFont = content.Load<SpriteFont>("Fonts/MainFont.font.xml");
	borderTexture = content.Load<Texture>("Hud/Border.png");
	heartTexture = content.Load<Texture>("Hud/Heart.png");
	hpBlockAtlas = content.Load<Spritesheet>("Hud/HP_Block.atlas.xml");

	knifeTexture = content.Load<Texture>("Hud/Knife.png");
}

void Hud::Draw(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(*heartTexture, heartTexturePosition, Color::White(), false);
	spriteBatch.Draw(*borderTexture, borderTexturePosition, Color::White(), false);

	auto weaponTexture = GetWeaponTexture();
	if (weaponTexture != nullptr)
		spriteBatch.Draw(*weaponTexture, GetWeaponPosition(*weaponTexture), Color::White(), false);

	spriteBatch.DrawString(*hudFont, GetScoreText(), scoreTextPosition, Color::White(), false);
	spriteBatch.DrawString(*hudFont, GetTimeText(), timeTextPosition, Color::White(), false);
	spriteBatch.DrawString(*hudFont, GetStageText(), stageTextPosition, Color::White(), false);

	spriteBatch.DrawString(*hudFont, "PLAYER", playerTextPosition, Color::White(), false);
	spriteBatch.DrawString(*hudFont, "ENEMY", enemyTextPosition, Color::White(), false);
	DrawHealthBars(spriteBatch);

	spriteBatch.DrawString(*hudFont, GetHeartCountText(), heartTextPosition, Color::White(), false);
	spriteBatch.DrawString(*hudFont, GetLiveCountText(), liveTextPosition, Color::White(), false);
}

std::string Hud::GetScoreText()
{
	return "SCORE-" + padZero(data.score, 6);
}

std::string Hud::GetTimeText()
{
	return "TIME " + padZero(data.timeLeft.GetCounter(), 4);
}

std::string Hud::GetStageText()
{
	return "STAGE " + padZero(data.stage, 2);
}

std::string Hud::GetHeartCountText()
{
	return "-" + padZero(data.hearts, 2);
}

std::string Hud::GetLiveCountText()
{
	return "P-" + padZero(data.lives, 2);
}

std::shared_ptr<Texture> Hud::GetWeaponTexture()
{
	switch (data.secondaryWeapon)
	{
		case EntityType::KnifeItem:
			return knifeTexture;

		default:
			return nullptr;
	}
}

Vector2 Hud::GetWeaponPosition(Texture &weaponTexture)
{
	auto borderCenter = Vector2{
		borderTexturePosition.x + borderTexture->Width() / 2,
		borderTexturePosition.y + borderTexture->Height() / 2 };

	auto weaponPosition = Vector2{
		borderCenter.x - weaponTexture.Width() / 2,
		borderCenter.y - weaponTexture.Height() / 2 };

	return weaponPosition;
}

void Hud::DrawHealthBars(SpriteExtensions &spriteBatch)
{
	for (auto i = 0; i < MAX_HEALTH; i++)
	{
		if (i <= data.playerHealth)
		{
			auto hpBlockTexture = hpBlockAtlas->at("player_full");
			auto position = Vector2{ playerHealthPosition.x + i * 9, playerHealthPosition.y };
			spriteBatch.Draw(hpBlockTexture, position, Color::White(), false);
		}
		else
		{
			auto hpBlockTexture = hpBlockAtlas->at("empty");
			auto position = Vector2{ playerHealthPosition.x + i * 9, playerHealthPosition.y };
			spriteBatch.Draw(hpBlockTexture, position, Color::White(), false);
		}

		if (i <= data.bossHealth)
		{
			auto hpBlockTexture = hpBlockAtlas->at("boss_full");
			auto position = Vector2{ enemyHealthPosition.x + i * 9, enemyHealthPosition.y };
			spriteBatch.Draw(hpBlockTexture, position, Color::White(), false);
		}
		else
		{
			auto hpBlockTexture = hpBlockAtlas->at("empty");
			auto position = Vector2{ enemyHealthPosition.x + i * 9, enemyHealthPosition.y };
			spriteBatch.Draw(hpBlockTexture, position, Color::White(), false);
		}
	}
}

std::string Hud::padZero(int number, int paddingCount)
{
	auto sstream = std::stringstream{};

	sstream << std::setfill('0') << std::setw(paddingCount) << number;

	return sstream.str();
}