#include "RenderingSystem.h"
#include "../../GameObject.h"

using namespace Castlevania;

auto NULL_GAME_OBJECT = GameObject{ EntityType::Unknown };

RenderingSystem::RenderingSystem()
{
	drawBoundingBox = true;
}

GameObject &RenderingSystem::GetParent()
{
	return NULL_GAME_OBJECT;
}

void RenderingSystem::DrawBoundingBox(bool value)
{
	drawBoundingBox = value;
}

void RenderingSystem::LoadContent(ContentManager &content)
{
	bboxTexture = content.Load<Texture>("Backgrounds/BoundingBox.png");
}

void RenderingSystem::Update(GameTime gameTime)
{
}

void RenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	if (drawBoundingBox)
	{
		auto boundingBox = GetSprite().GetBoundingRectangle(GetParent().GetPosition());
		auto position = Vector2{ boundingBox.X(), boundingBox.Y() };
		auto color = GetBoundingBoxColor();

		spriteBatch.Draw(*bboxTexture, position, &(Rect)boundingBox, color, 0.0f, Vector2::One(), SpriteEffects::None);
	}
}

Color RenderingSystem::GetBoundingBoxColor()
{
	auto type = (EntityType)GetParent().GetType();
	auto bboxColorScale = 0.65f;

	switch (type)
	{
		case EntityType::Boundary:
			return Color::Blue() * bboxColorScale;

		case EntityType::SpawnArea:
			return Color::Red() * bboxColorScale;

		case EntityType::Player:
			return Color::LavenderBlue() * bboxColorScale;

		case EntityType::Brazier:
			return Color::Green() * bboxColorScale;

		case EntityType::Whip:
			return Color::Red() * bboxColorScale;

			// Just a fg image, skip drawing
		case EntityType::Castle:
			return Color::Transparent();

		default:
			return Color::Magenta() * bboxColorScale;
	}
}
