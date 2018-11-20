#include <iomanip>
#include <sstream>
#include "Hud.h"

using namespace Castlevania;

Hud::Hud(const PlayerData &data) : data{ data }
{
	scoreTextPosition = Vector2{ 0, 15 }; // TODO: dont hardcode position
	timeTextPosition = Vector2{ 200, 15 };
	stageTextPosition = Vector2{ 370, 15 };
	playerTextPosition = Vector2{ 0, 32 };
	enemyTextPosition = Vector2{ 2, 49 };
	borderTexturePosition = Vector2{ 250, 32 };
	heartTexturePosition = Vector2{ 335, 32 };
	heartTextPosition = Vector2{ 350, 32 };
}

void Hud::LoadContent(ContentManager &content)
{
	hudFont = content.Load<SpriteFont>("Fonts/MainFont");
	borderTexture = content.Load<Texture>("Hud/Border.png");
	heartTexture = content.Load<Texture>("Hud/Heart.png");
}

void Hud::Draw(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(*heartTexture, heartTexturePosition, Color::White(), false);
	spriteBatch.Draw(*borderTexture, borderTexturePosition, Color::White(), false);

	spriteBatch.DrawString(*hudFont, GetScoreText(), scoreTextPosition, Color::White(), false);
	spriteBatch.DrawString(*hudFont, GetTimeText(), timeTextPosition, Color::White(), false);
	spriteBatch.DrawString(*hudFont, GetStageText(), stageTextPosition, Color::White(), false);
	spriteBatch.DrawString(*hudFont, "PLAYER", playerTextPosition, Color::White(), false);
	spriteBatch.DrawString(*hudFont, "ENEMY", enemyTextPosition, Color::White(), false);
	spriteBatch.DrawString(*hudFont, GetHeartText(), heartTextPosition, Color::White(), false);
	//spriteBatch.DrawString(*hudFont, pText, stageTextPosition, Color::White());
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

std::string Hud::GetHeartText()
{
	return "-" + padZero(data.hearts, 2);
}

std::string Hud::GetPText()
{
	return "P-" + padZero(data.p, 2);
}

std::string Hud::padZero(int number, int paddingCount)
{
	auto sstream = std::stringstream{};

	sstream << std::setfill('0') << std::setw(paddingCount) << number;

	return sstream.str();
}
