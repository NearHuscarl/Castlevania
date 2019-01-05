#include "RenderingSystem.h"
#include "../../GameObject.h"
#include "../../Settings.h"
#include "../../../Utilities/DevTool.h"

using namespace Castlevania;

std::shared_ptr<Texture> RenderingSystem::bboxTexture = nullptr;

RenderingSystem::RenderingSystem()
{
}

GameObject &RenderingSystem::GetParent()
{
	return GameObject::NullObject();
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

		case TAKING_DAMAGE:
			OnTakingDamage();
			break;

	}
}

void RenderingSystem::LoadContent(ContentManager &content)
{
	bboxTexture = content.Load<Texture>("Backgrounds/BoundingBox.png");
}

void RenderingSystem::DrawBoundingBox(SpriteExtensions &spriteBatch, RectF boundingBox, Color color)
{
	auto position = Vector2{ boundingBox.X(), boundingBox.Y() };

	spriteBatch.Draw(*bboxTexture, position, &(Rect)boundingBox, color, 0.0f, Vector2::One(), SpriteEffects::None);
}

void RenderingSystem::Update(GameTime gameTime)
{
}

void RenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	if (DevTool::IsDebugging && GetParent().GetSprite()->IsVisible())
	{
		auto boundingBox = GetSprite().GetBoundingRectangle(GetParent().GetPosition());
		auto color = GetBoundingBoxColor();

		DrawBoundingBox(spriteBatch, boundingBox, color);
	}
}

void RenderingSystem::OnMoveStateChanged()
{
}

void RenderingSystem::OnStateChanged()
{
}

void RenderingSystem::OnTakingDamage()
{
}

Color RenderingSystem::GetBoundingBoxColor()
{
	auto objectId = GetParent().GetId();
	auto bboxColorScale = 0.65f;

	switch (objectId)
	{
		case ObjectId::Boundary:
			return Color::DimGray() * bboxColorScale;

		case ObjectId::SpawnArea:
		case ObjectId::SpawnPoint:
			return Color::Red() * (bboxColorScale - 0.2f);

		case ObjectId::BossFightArea:
			return Color::DimGray() * (bboxColorScale - 0.3f);

		case ObjectId::WaterArea:
			return Color::Blue() * bboxColorScale;

		case ObjectId::Player:
			return Color::Gold() * bboxColorScale;

		case ObjectId::Brazier:
		case ObjectId::Candle:
			return Color::YellowGreen() * bboxColorScale;

		case ObjectId::Zombie:
		case ObjectId::Panther:
		case ObjectId::VampireBat:
		case ObjectId::Fishman:
			return Color::Green();

		case ObjectId::Whip:
			return Color::Red() * bboxColorScale;

			// Just a fg image, skip drawing
		case ObjectId::Castle:
		case ObjectId::StageArea:
			return Color::Transparent();

		default:
			return Color::Magenta() * bboxColorScale;
	}
}
