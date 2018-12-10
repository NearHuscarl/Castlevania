#include "Direct2DGame/MathHelper.h"
#include "Direct2DGame/Input/InputHelper.h"
#include "DevTool.h"
#include "TypeConverter.h"

using namespace Castlevania;

constexpr auto ENEMY = "ENEMY";
constexpr auto CONTAINER = "CONTAINER";
constexpr auto ITEM = "ITEM";

DevTool::DevTool(ObjectFactory &objectFactory, Camera &camera) :
	objectFactory{ objectFactory },
	camera{ camera }
{
	currentItemIndex = 0;
}

void DevTool::LoadContent(ContentManager &content)
{
	debugFont = content.Load<SpriteFont>("Fonts/DebugFont.font.xml");

	auto zombieSprite = content.Load<Spritesheet>("Characters/Enemies/Zombie.atlas.xml")->begin()->second;
	auto pantherSprite = content.Load<Spritesheet>("Characters/Enemies/Panther.atlas.xml")->begin()->second;
	auto fishmanSprite = content.Load<Spritesheet>("Characters/Enemies/Fishman.atlas.xml")->begin()->second;
	auto vampireBatSprite = content.Load<Spritesheet>("Characters/Enemies/VampireBat.atlas.xml")->at("fly_01");
	auto brazierSprite = content.Load<Spritesheet>("Items/Brazier.atlas.xml")->begin()->second;
	auto candleSprite = content.Load<Spritesheet>("Items/Candle.atlas.xml")->begin()->second;
	auto daggerItemSprite = content.Load<Texture>("Items/Dagger.png");
	auto largeHeartSprite = content.Load<Texture>("Items/Large_Heart.png");
	auto whipPowerupSprite = content.Load<Texture>("Items/Whip_Powerup.png");

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
			ITEM,
			{
				std::make_pair<std::string, Sprite>("DaggerItem", daggerItemSprite),
				std::make_pair<std::string, Sprite>("LargeHeart", largeHeartSprite),
				std::make_pair<std::string, Sprite>("WhipPowerup", whipPowerupSprite),
			}
		},
	};

	category = items.begin()->first;
}

void DevTool::Update(ObjectCollection &objectCollection)
{
	// Update keyboard input
	if (InputHelper::IsKeyDown(DIK_ESCAPE))
	{
		isDebugging = !isDebugging;
	}

	if (!isDebugging)
		return;

	if (InputHelper::IsKeyDown(DIK_Q))
	{
		category = ENEMY;
	}
	else if (InputHelper::IsKeyDown(DIK_W))
	{
		category = CONTAINER;
	}
	else if (InputHelper::IsKeyDown(DIK_E))
	{
		category = ITEM;
	}

	// Update mouse input
	if (InputHelper::IsScrollingDown())
	{
		if (--currentItemIndex < 0)
			currentItemIndex = items[category].size() - 1;
	}
	else if (InputHelper::IsScrollingUp())
	{
		if (++currentItemIndex > (int)items[category].size() - 1)
			currentItemIndex = 0;
	}
	else if (InputHelper::IsMouseReleased(MouseButton::Left))
	{
		auto type = string2EntityType.at(items[category][currentItemIndex].first);
		auto objectPosition = GetCurrentItemPosition();
		auto object = std::unique_ptr<GameObject>{};

		if (category == ENEMY)
		{
			object = objectFactory.CreateEnemy(type);
		}
		else if (category == ITEM)
		{
			object = objectFactory.CreatePowerup(type);
		}
		else if (category == CONTAINER)
		{
			auto powerupIndex = MathHelper::RandomBetween(0, (int)items[ITEM].size() - 1);
			auto powerupType = string2EntityType.at(items[ITEM][powerupIndex].first);
			switch (type)
			{
				// TODO: randomize powerup
				case EntityType::Brazier:
					object = objectFactory.CreateBrazier(powerupType);
					break;
				case EntityType::Candle:
					object = objectFactory.CreateCandle(powerupType);
					break;
			}
		}

		object->SetPosition(objectPosition);
		object->SetFacing(currentFacing);
		objectCollection.entities.push_back(std::move(object));
	}
	else if (InputHelper::IsMouseReleased(MouseButton::Right))
	{
		if (currentFacing == Facing::Left)
			currentFacing = Facing::Right;
		else
			currentFacing = Facing::Left;
	}
}

void DevTool::Draw(SpriteExtensions &spriteBatch)
{
	if (!isDebugging)
		return;

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
	auto sprite = items[category][currentItemIndex].second;
	auto mousePosition = camera.ScreenToWorld(InputHelper::GetMousePosition());
	auto position = Vector2{ mousePosition.x - sprite.GetFrameRectangle(mousePosition).Width(), mousePosition.y };

	return position;
}
