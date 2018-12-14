#include "Direct2DGame/MathHelper.h"
#include "Direct2DGame/Input/InputHelper.h"
#include "DevTool.h"
#include "TypeConverter.h"
#include "CppExtensions.h"
#include "../Scenes/GameplayScene.h"
#include "../Scenes/SceneManager.h"

using namespace Castlevania;

int DevTool::currentItemIndex = 0;
int DevTool::currentMapIndex = 0;

constexpr auto ENEMY = "ENEMY";
constexpr auto CONTAINER = "CONTAINER";
constexpr auto POWERUP = "POWERUP";
constexpr auto EFFECT = "EFFECT";
constexpr auto OTHER = "OTHER";

DevTool::DevTool(GameplayScene &gameplayScene, Camera &camera) :
	gameplayScene{ gameplayScene },
	objectFactory{ gameplayScene.GetSceneManager().GetFactory() },
	camera{ camera }
{
	isDebugging = true;
}

void DevTool::LoadContent(ContentManager &content)
{
	debugFont = content.Load<SpriteFont>("Fonts/DebugFont.font.xml");
	effectFactory = std::make_unique<EffectFactory>(content);

	auto zombieSprite = content.Load<Spritesheet>("Characters/Enemies/Zombie.atlas.xml")->begin()->second;
	auto pantherSprite = content.Load<Spritesheet>("Characters/Enemies/Panther.atlas.xml")->begin()->second;
	auto fishmanSprite = content.Load<Spritesheet>("Characters/Enemies/Fishman.atlas.xml")->begin()->second;
	auto vampireBatSprite = content.Load<Spritesheet>("Characters/Enemies/VampireBat.atlas.xml")->at("fly_01");
	auto brazierSprite = content.Load<Spritesheet>("Items/Brazier.atlas.xml")->begin()->second;
	auto candleSprite = content.Load<Spritesheet>("Items/Candle.atlas.xml")->begin()->second;
	auto blueMoneyBagSprite = content.Load<Spritesheet>("Items/Money_Bag.atlas.xml")->at("money_bag_blue");
	auto whiteMoneyBagSprite = content.Load<Spritesheet>("Items/Money_Bag.atlas.xml")->at("money_bag_white");
	auto redMoneyBagSprite = content.Load<Spritesheet>("Items/Money_Bag.atlas.xml")->at("money_bag_red");
	auto daggerItemSprite = content.Load<Texture>("Items/Dagger.png");
	auto largeHeartSprite = content.Load<Texture>("Items/Large_Heart.png");
	auto smallHeartSprite = content.Load<Texture>("Items/Small_Heart.png");
	auto whipPowerupSprite = content.Load<Texture>("Items/Whip_Powerup.png");
	auto flameSprite = content.Load<Spritesheet>("Effects/Flame.atlas.xml")->at("flame_02");
	auto waterSprite = content.Load<Texture>("Effects/Water.png");
	auto fireballSprite = content.Load<Texture>("Items/Fireball.png");

	items = std::unordered_map<std::string, DevToolItems>{
		{
			ENEMY,
			{
				std::make_pair<std::string, Sprite>("Zombie", zombieSprite),
				std::make_pair<std::string, Sprite>("Panther", pantherSprite),
				std::make_pair<std::string, Sprite>("Fishman", fishmanSprite),
				std::make_pair<std::string, Sprite>("VampireBat", vampireBatSprite),
			},
		},
		{
			CONTAINER,
			{
				std::make_pair<std::string, Sprite>("Brazier", brazierSprite),
				std::make_pair<std::string, Sprite>("Candle", candleSprite),
			}
		},
		{
			POWERUP,
			{
				std::make_pair<std::string, Sprite>("BlueMoneyBag", blueMoneyBagSprite),
				std::make_pair<std::string, Sprite>("WhiteMoneyBag", whiteMoneyBagSprite),
				std::make_pair<std::string, Sprite>("RedMoneyBag", redMoneyBagSprite),
				std::make_pair<std::string, Sprite>("FlashingMoneyBag", blueMoneyBagSprite),
				std::make_pair<std::string, Sprite>("DaggerItem", daggerItemSprite),
				std::make_pair<std::string, Sprite>("LargeHeart", largeHeartSprite),
				std::make_pair<std::string, Sprite>("SmallHeart", smallHeartSprite),
				std::make_pair<std::string, Sprite>("WhipPowerup", whipPowerupSprite),
			}
		},
		{
			EFFECT,
			{
				std::make_pair<std::string, Sprite>("FlameEffect", flameSprite),
				std::make_pair<std::string, Sprite>("WaterEffect", waterSprite),
			}
		},
		{
			OTHER,
			{
				std::make_pair<std::string, Sprite>("Fireball", fireballSprite),
			}
		},
	};

	category = items.begin()->first;

	maps = std::vector<Map>{ Map::COURTYARD, Map::GREAT_HALL, Map::UNDERGROUND, Map::PLAYGROUND };
}

void DevTool::Update(GameTime gameTime, ObjectCollection &objectCollection)
{
	UpdateEffects(gameTime);

	// Update keyboard input
	if (InputHelper::IsKeyDown(DIK_ESCAPE))
		isDebugging = !isDebugging;

	if (!isDebugging)
		return;

	if (InputHelper::IsKeyDown(DIK_Q))
		SetCategory(ENEMY);
	else if (InputHelper::IsKeyDown(DIK_W))
		SetCategory(CONTAINER);
	else if (InputHelper::IsKeyDown(DIK_E))
		SetCategory(POWERUP);
	else if (InputHelper::IsKeyDown(DIK_R))
		SetCategory(EFFECT);
	else if (InputHelper::IsKeyDown(DIK_T))
		SetCategory(OTHER);

	else if (InputHelper::IsKeyDown(DIK_HOME))
		NextMap();
	else if (InputHelper::IsKeyDown(DIK_END))
		PreviousMap();

	else if (InputHelper::IsKeyDown(DIK_1))
		gameplayScene.GetPlayer()->SetPosition(objectCollection.locations["Checkpoint"]);
	else if (InputHelper::IsKeyDown(DIK_2))
		gameplayScene.GetPlayer()->SetPosition(objectCollection.locations["Checkpoint_02"]);
	else if (InputHelper::IsKeyDown(DIK_3))
		gameplayScene.GetPlayer()->SetPosition(objectCollection.locations["Checkpoint_03"]);
	else if (InputHelper::IsKeyDown(DIK_4))
		gameplayScene.GetPlayer()->SetPosition(objectCollection.locations["Checkpoint_04"]);
	else if (InputHelper::IsKeyDown(DIK_5))
		gameplayScene.GetPlayer()->SetPosition(objectCollection.locations["Checkpoint_05"]);
	else if (InputHelper::IsKeyDown(DIK_6))
		gameplayScene.GetPlayer()->SetPosition(objectCollection.locations["Checkpoint_06"]);

	// Update mouse input
	if (InputHelper::IsScrollingDown())
		PreviousItem();
	else if (InputHelper::IsScrollingUp())
		NextItem();
	else if (InputHelper::IsMouseReleased(MouseButton::Left))
		SpawnItem(objectCollection);
	else if (InputHelper::IsMouseReleased(MouseButton::Right))
		currentFacing = Opposite(currentFacing);
}

void DevTool::Draw(SpriteExtensions &spriteBatch)
{
	if (!isDebugging)
		return;

	for (auto effect : activeEffects)
		effect->Draw(spriteBatch);

	auto objectPosition = GetCurrentItemPosition();
	auto textPosition = Vector2{ objectPosition.x, objectPosition.y - 20 };
	auto effect = currentFacing == Facing::Left ? SpriteEffects::FlipHorizontally : SpriteEffects::None;
	auto itemName = items[category][currentItemIndex].first;
	auto sprite = items[category][currentItemIndex].second;
	
	sprite.SetEffect(effect);

	spriteBatch.DrawString(*debugFont, itemName, textPosition, Color::White());
	spriteBatch.Draw(sprite, objectPosition);
}

Vector2 DevTool::GetCurrentItemPosition()
{
	auto mousePosition = camera.ScreenToWorld(InputHelper::GetMousePosition());
	auto sprite = items[category][currentItemIndex].second;
	auto spriteWidth = sprite.GetFrameRectangle(mousePosition).Width();
	
	return Vector2{ mousePosition.x - spriteWidth, mousePosition.y };
}

std::unique_ptr<IEffect> DevTool::CreateEffect(std::string name)
{
	if (name == "FlameEffect")
		return effectFactory->CreateFlameEffect();
	else if (name == "WaterEffect")
		return effectFactory->CreateWaterEffect();
	else
		throw std::runtime_error("Effect name is invalid");
}

void DevTool::UpdateEffects(GameTime gameTime)
{
	for (int i = activeEffects.size() - 1; i >= 0; i--)
	{
		activeEffects[i]->Update(gameTime);

		if (activeEffects[i]->IsFinished())
			RemoveByValue(activeEffects, activeEffects[i]);
	}
}

void DevTool::SetCategory(std::string category)
{
	this->category = category;
	this->currentItemIndex = 0;
}

void DevTool::NextItem()
{
	if (++currentItemIndex > (int)items[category].size() - 1)
		currentItemIndex = 0;
}

void DevTool::PreviousItem()
{
	if (--currentItemIndex < 0)
		currentItemIndex = items[category].size() - 1;
}

void DevTool::SpawnItem(ObjectCollection &objectCollection)
{
	if (category == EFFECT)
		SpawnEffect();
	else
		SpawnObject(objectCollection);
}

void DevTool::SpawnObject(ObjectCollection &objectCollection)
{
	auto type = string2EntityType.at(items[category][currentItemIndex].first);
	auto objectPosition = GetCurrentItemPosition();
	auto object = std::unique_ptr<GameObject>{};

	if (category == ENEMY)
	{
		object = objectFactory.CreateEnemy(type);
	}
	else if (category == POWERUP)
	{
		object = objectFactory.CreatePowerup(type);
	}
	else if (category == CONTAINER)
	{
		auto powerupIndex = MathHelper::RandomBetween(0, (int)items[POWERUP].size() - 1);
		auto powerupType = string2EntityType.at(items[POWERUP][powerupIndex].first);
		switch (type)
		{
			case EntityType::Brazier:
				object = objectFactory.CreateBrazier(powerupType);
				break;
			case EntityType::Candle:
				object = objectFactory.CreateCandle(powerupType);
				break;
		}
	}
	else if (category == OTHER)
	{
		switch (type)
		{
			case EntityType::Fireball:
				object = objectFactory.CreateFireball();
				if (currentFacing == Facing::Right)
					object->SetVelocity_X(object->GetSpeed());
				else
					object->SetVelocity_X(-object->GetSpeed());
				break;
		}
	}

	object->SetPosition(objectPosition);
	object->SetFacing(currentFacing);
	objectCollection.entities.push_back(std::move(object));
}

void DevTool::SpawnEffect()
{
	auto effectName = items[EFFECT][currentItemIndex].first;
	auto effect = CreateEffect(effectName);

	effect->Show(GetCurrentItemPosition());
	activeEffects.push_back(std::move(effect));
}

void DevTool::NextMap()
{
	if (++currentMapIndex > (int)maps.size() - 1)
		currentMapIndex = 0;

	gameplayScene.NextStage(maps[currentMapIndex]);
}

void DevTool::PreviousMap()
{
	if (--currentMapIndex < 0)
		currentMapIndex = maps.size() - 1;

	gameplayScene.NextStage(maps[currentMapIndex]);
}
