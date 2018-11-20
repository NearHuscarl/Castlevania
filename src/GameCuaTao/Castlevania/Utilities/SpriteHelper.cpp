#include "SpriteHelper.h"

using namespace Castlevania;

std::shared_ptr<Texture> SpriteHelper::boundingBoxTexture = nullptr;

void SpriteHelper::LoadContent(ContentManager &content)
{
	boundingBoxTexture = content.Load<Texture>("Textures/Backgrounds/BoundingBox.png");
}

void SpriteHelper::DrawRectangle(SpriteBatch &spriteBatch, RectF rect, Color color)
{
	auto position = Vector2{ rect.X(), rect.Y() };

	spriteBatch.Draw(*boundingBoxTexture, position, &(Rect)rect, color, 0.0f, Vector2::One(), SpriteEffects::None);
}
