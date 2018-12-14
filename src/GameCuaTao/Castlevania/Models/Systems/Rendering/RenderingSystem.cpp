#include "RenderingSystem.h"
#include "../../GameObject.h"
#include "../../Settings.h"

using namespace Castlevania;

RenderingSystem::RenderingSystem()
{
	drawBoundingBox = true;
}

GameObject &RenderingSystem::GetParent()
{
	return GameObject::NullObject();
}

void RenderingSystem::DrawBoundingBox(bool value)
{
	drawBoundingBox = value;
}

void RenderingSystem::Receive(int message)
{
	switch (message)
	{
		case MOVE_STATE_CHANGED:
			OnMoveStateChanged();
			break;

		case STATE_CHANGED:
			OnStateChanged();
			break;
	}
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
	if (drawBoundingBox && GetParent().GetSprite()->IsVisible())
	{
		auto boundingBox = GetSprite().GetBoundingRectangle(GetParent().GetPosition());
		auto position = Vector2{ boundingBox.X(), boundingBox.Y() };
		auto color = GetBoundingBoxColor();

		spriteBatch.Draw(*bboxTexture, position, &(Rect)boundingBox, color, 0.0f, Vector2::One(), SpriteEffects::None);
	}
}

void RenderingSystem::DrawBoundingBox(SpriteExtensions &spriteBatch, RectF boundingBox, Color color)
{
	auto position = Vector2{ boundingBox.X(), boundingBox.Y() };

	spriteBatch.Draw(*bboxTexture, position, &(Rect)boundingBox, color, 0.0f, Vector2::One(), SpriteEffects::None);
}

void RenderingSystem::OnMoveStateChanged()
{
}

void RenderingSystem::OnStateChanged()
{
}

Color RenderingSystem::GetBoundingBoxColor()
{
	auto type = (EntityType)GetParent().GetType();
	auto bboxColorScale = 0.65f;

	switch (type)
	{
		case EntityType::Boundary:
			return Color::DimGray() * bboxColorScale;

		case EntityType::SpawnArea:
		case EntityType::SpawnPoint:
			return Color::Red() * (bboxColorScale - 0.2f);

		case EntityType::WaterArea:
			return Color::Blue() * bboxColorScale;

		case EntityType::Player:
			return Color::Gold() * bboxColorScale;

		case EntityType::Brazier:
			return Color::YellowGreen() * bboxColorScale;

		case EntityType::Zombie:
		case EntityType::Panther:
		case EntityType::VampireBat:
		case EntityType::Fishman:
			return Color::Green();

		case EntityType::Whip:
			return Color::Red() * bboxColorScale;

			// Just a fg image, skip drawing
		case EntityType::Castle:
		case EntityType::ViewportArea:
			return Color::Transparent();

		default:
			return Color::Magenta() * bboxColorScale;
	}
}
