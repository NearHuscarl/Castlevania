#include "Direct2DGame/Input/InputHelper.h"
#include "DevTool.h"
#include "TypeConverter.h"

using namespace Castlevania;

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
	auto daggerItemSprite = content.Load<Texture>("Items/Dagger.png");
	auto largeHeartSprite = content.Load<Texture>("Items/Large_Heart.png");
	auto whipPowerupSprite = content.Load<Texture>("Items/Whip_Powerup.png");

	items = DevToolItems
	{
		std::make_pair<std::string, Sprite>("Zombie", zombieSprite),
		std::make_pair<std::string, Sprite>("Panther", pantherSprite),
		std::make_pair<std::string, Sprite>("Fishman", fishmanSprite),
		std::make_pair<std::string, Sprite>("VampireBat", vampireBatSprite),
		std::make_pair<std::string, Sprite>("DaggerItem", daggerItemSprite),
		std::make_pair<std::string, Sprite>("LargeHeart", largeHeartSprite),
		std::make_pair<std::string, Sprite>("WhipPowerup", whipPowerupSprite),
	};
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

	// Update mouse input
	if (InputHelper::IsScrollingDown())
	{
		if (--currentItemIndex < 0)
			currentItemIndex = items.size() - 1;
	}
	else if (InputHelper::IsScrollingUp())
	{
		if (++currentItemIndex > (int)items.size() - 1)
			currentItemIndex = 0;
	}
	else if (InputHelper::IsMouseReleased(MouseButton::Left))
	{
		auto type = string2EntityType.at(items[currentItemIndex].first);
		auto objectPosition = GetCurrentItemPosition();
		auto object = std::unique_ptr<GameObject>{};

		switch (type)
		{
			case EntityType::Zombie:
				object = objectFactory.CreateZombie(objectPosition);
				break;
			case EntityType::Panther:
				object = objectFactory.CreatePanther(objectPosition);
				break;
			case EntityType::Fishman:
				object = objectFactory.CreateFishman(objectPosition);
				dynamic_cast<Fishman&>(*object).Launch();
				break;
			case EntityType::VampireBat:
				object = objectFactory.CreateVampireBat(objectPosition);
				break;
			case EntityType::DaggerItem:
				object = objectFactory.CreateDaggerItem(objectPosition);
				break;
			case EntityType::LargeHeart:
				object = objectFactory.CreateLargeHeart(objectPosition);
				break;
			case EntityType::WhipPowerup:
				object = objectFactory.CreateWhipPowerup(objectPosition);
				break;
		}
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
	auto sprite = items[currentItemIndex].second;
	
	sprite.SetEffect(effect);

	spriteBatch.DrawString(*debugFont, items[currentItemIndex].first, textPosition, Color::White());
	spriteBatch.Draw(sprite, objectPosition);
}

Vector2 DevTool::GetCurrentItemPosition()
{
	auto sprite = items[currentItemIndex].second;
	auto mousePosition = camera.ScreenToWorld(InputHelper::GetMousePosition());
	auto position = Vector2{ mousePosition.x - sprite.GetFrameRectangle(mousePosition).Width(), mousePosition.y };

	return position;
}
