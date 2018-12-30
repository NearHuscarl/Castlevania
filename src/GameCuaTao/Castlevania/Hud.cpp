#include <iomanip>
#include <sstream>
#include "Direct2DGame/MathHelper.h"
#include "Hud.h"

using namespace Castlevania;

constexpr auto HUD_HEIGHT = 83;
constexpr auto POWERUP_FLASHING_TIME = 2500;

const auto DEFAULT_PLAYER_DATA = PlayerData{};
const auto DEFAULT_BOSS_HEALTH = Health{ MAX_HEALTH };
const auto DEFAULT_GAMEPLAY_DATA = GameplayData{};

struct Hud::HudData
{
	const PlayerData *playerData;
	const Health *bossHealth;
	const GameplayData *gameplayData;
};

Hud::Hud(GraphicsDevice &graphicsDevice)
{
	width = graphicsDevice.GetViewport().width;
	height = HUD_HEIGHT;
	data = std::make_unique<HudData>();

	data->playerData = &DEFAULT_PLAYER_DATA;
	data->bossHealth = &DEFAULT_BOSS_HEALTH;
	data->gameplayData = &DEFAULT_GAMEPLAY_DATA;

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
	powerupPosition = Vector2{ 432, 48 };
}

int Hud::GetWidth()
{
	return width;
}

int Hud::GetHeight()
{
	return height;
}

void Hud::Register(const PlayerData &playerData)
{
	data->playerData = &playerData;
}

void Hud::Register(const Health &bossHealth)
{
	data->bossHealth = &bossHealth;
}

void Hud::Register(const GameplayData &gameplayData)
{
	data->gameplayData = &gameplayData;
}

template<>
void Hud::Unregister<PlayerData>()
{
	data->playerData = &DEFAULT_PLAYER_DATA;
}

template<>
void Hud::Unregister<int>()
{
	data->bossHealth = &DEFAULT_BOSS_HEALTH;
}

template<>
void Hud::Unregister<GameplayData>()
{
	data->gameplayData = &DEFAULT_GAMEPLAY_DATA;
}

void Hud::LoadContent(ContentManager &content)
{
	hudFont = content.Load<SpriteFont>("Fonts/MainFont.font.xml");
	borderTexture = content.Load<Texture>("Hud/Border.png");
	heartTexture = content.Load<Texture>("Hud/Heart.png");
	
	auto hpBlockAtlas = content.Load<Spritesheet>("Hud/HP_Block.atlas.xml");
	
	playerFullBlock = std::make_unique<Sprite>(hpBlockAtlas->at("player_full"));
	bossFullBlock = std::make_unique<Sprite>(hpBlockAtlas->at("boss_full"));
	emptyBlock = std::make_unique<Sprite>(hpBlockAtlas->at("empty"));

	axeTexture = content.Load<Texture>("Items/Axe.png");
	daggerTexture = content.Load<Texture>("Items/Dagger.png");
	holyWaterTexture = content.Load<Texture>("Items/Holy_Water.png");
	stopwatchTexture = content.Load<Texture>("Items/Stopwatch.png");
	doubleShotTexture = content.Load<Texture>("Hud/Double_Shot.png");
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
	DrawHealthBars(spriteBatch);

	auto weaponTexture = GetWeaponTexture();
	if (weaponTexture != nullptr)
		spriteBatch.Draw(*weaponTexture, GetWeaponPosition(*weaponTexture), Color::White(), false);

	spriteBatch.DrawString(*hudFont, GetHeartCountText(), heartTextPosition, Color::White(), false);
	spriteBatch.DrawString(*hudFont, GetLiveCountText(), liveTextPosition, Color::White(), false);
	
	DrawPowerup(spriteBatch);
}

std::string Hud::GetScoreText()
{
	return "SCORE-" + PadZero(data->playerData->score, 6);
}

std::string Hud::GetTimeText()
{
	return "TIME " + PadZero(MathHelper::Max(data->gameplayData->timeLeft.GetCounter(), 0), 4);
}

std::string Hud::GetStageText()
{
	return "STAGE " + PadZero(data->gameplayData->stage, 2);
}

std::string Hud::GetHeartCountText()
{
	return "-" + PadZero(data->playerData->hearts, 2);
}

std::string Hud::GetLiveCountText()
{
	return "P-" + PadZero(data->playerData->lives, 2);
}

std::shared_ptr<Texture> Hud::GetWeaponTexture()
{
	switch (data->playerData->subWeapon)
	{
		case ObjectId::AxeItem:
			return axeTexture;

		case ObjectId::DaggerItem:
			return daggerTexture;

		case ObjectId::HolyWaterItem:
			return holyWaterTexture;

		case ObjectId::Stopwatch:
			return stopwatchTexture;

		default:
			return nullptr;
	}
}

std::shared_ptr<Texture> Hud::GetPowerupTexture()
{
	switch (data->playerData->powerup)
	{
		case ObjectId::DoubleShot:
			return doubleShotTexture;

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

Vector2 Hud::GetPowerupPosition(Texture &powerupTexture)
{
	return Vector2{
		powerupPosition.x - powerupTexture.Width() / 2,
		powerupPosition.y - powerupTexture.Height() / 2 };
}

void Hud::DrawHealthBars(SpriteExtensions &spriteBatch)
{
	auto playerHealth = data->playerData->health.Value();
	auto bossHealth = data->bossHealth->Value();

	for (auto i = 0; i < MAX_HEALTH; i++)
	{
		if (i + 1 <= playerHealth)
		{
			auto position = Vector2{ playerHealthPosition.x + i * 9, playerHealthPosition.y };
			spriteBatch.Draw(*playerFullBlock, position, false);
		}
		else
		{
			auto position = Vector2{ playerHealthPosition.x + i * 9, playerHealthPosition.y };
			spriteBatch.Draw(*emptyBlock, position, false);
		}

		if (i + 1 <= bossHealth)
		{
			auto position = Vector2{ enemyHealthPosition.x + i * 9, enemyHealthPosition.y };
			spriteBatch.Draw(*bossFullBlock, position, false);
		}
		else
		{
			auto position = Vector2{ enemyHealthPosition.x + i * 9, enemyHealthPosition.y };
			spriteBatch.Draw(*emptyBlock, position, false);
		}
	}
}

void Hud::DrawPowerup(SpriteExtensions &spriteBatch)
{
	auto currentPowerupTexture = GetPowerupTexture();

	if (currentPowerupTexture == nullptr)
		return;

	if (powerupTexture == nullptr && currentPowerupTexture != nullptr)
		powerupFlashingTimer.Start();

	if (powerupFlashingTimer.IsRunning())
	{
		if (powerupFlashingTimer.ElapsedMilliseconds() >= POWERUP_FLASHING_TIME)
			powerupFlashingTimer.Reset();
		else
			spriteBatch.Draw(*currentPowerupTexture, GetPowerupPosition(*currentPowerupTexture),
				Stopwatch::Every(60) ? Color::White() : Color::Transparent(), false);
	}
	else
		spriteBatch.Draw(*currentPowerupTexture, GetPowerupPosition(*currentPowerupTexture), Color::White(), false);
	
	powerupTexture = currentPowerupTexture;
}

std::string Hud::PadZero(int number, int paddingCount)
{
	auto sstream = std::stringstream{};

	sstream << std::setfill('0') << std::setw(paddingCount) << number;

	return sstream.str();
}

Hud::~Hud() = default;
