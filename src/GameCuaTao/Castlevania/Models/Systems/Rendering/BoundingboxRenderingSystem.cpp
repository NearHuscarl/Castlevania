#include "BoundingboxRenderingSystem.h"
#include "../../GameObject.h"

using namespace Castlevania;

BoundingBoxRenderingSystem::BoundingBoxRenderingSystem(GameObject &parent, RectF boundingBox) :
	parent{ parent }
{
	this->boundingBox = boundingBox;
}

Sprite &BoundingBoxRenderingSystem::GetSprite()
{
	return *sprite;
}

GameObject &BoundingBoxRenderingSystem::GetParent()
{
	return parent;
}

void BoundingBoxRenderingSystem::LoadContent(ContentManager &content)
{
	RenderingSystem::LoadContent(content);

	auto textureRegion = TextureRegion{ bboxTexture, (Rect)boundingBox };
	sprite = std::make_unique<Sprite>(textureRegion);
}

void BoundingBoxRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	RenderingSystem::Draw(spriteBatch);

	if (DrawDebug())
	{
		auto leftLine = RectF{ boundingBox.left, boundingBox.top, 1, boundingBox.Height() };
		auto topLine = RectF{ boundingBox.left, boundingBox.top, boundingBox.Width(), 1 };
		auto rightLine = RectF{ boundingBox.right, boundingBox.top, 1, boundingBox.Height() };
		auto bottomLine = RectF{ boundingBox.left, boundingBox.bottom, boundingBox.Width(), 1 };
		auto borderColor = Color::DimGray();

		DrawBoundingBox(spriteBatch, leftLine, borderColor);
		DrawBoundingBox(spriteBatch, topLine, borderColor);
		DrawBoundingBox(spriteBatch, rightLine, borderColor);
		DrawBoundingBox(spriteBatch, bottomLine, borderColor);
	}
}
