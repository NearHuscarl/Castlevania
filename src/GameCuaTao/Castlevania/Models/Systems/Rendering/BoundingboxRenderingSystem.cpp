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
