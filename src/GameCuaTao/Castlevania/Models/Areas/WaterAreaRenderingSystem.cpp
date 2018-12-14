#include "WaterAreaRenderingSystem.h"
#include "../../Utilities/CppExtensions.h"

using namespace Castlevania;

WaterAreaRenderingSystem::WaterAreaRenderingSystem(WaterArea &parent) : parent{ parent }
{
}

Sprite &WaterAreaRenderingSystem::GetSprite()
{
	return *sprite;
}

GameObject &WaterAreaRenderingSystem::GetParent()
{
	return parent;
}

void WaterAreaRenderingSystem::LoadContent(ContentManager &content)
{
	RenderingSystem::LoadContent(content);

	auto textureRegion = TextureRegion{ bboxTexture, (Rect)parent.GetBoundingBox() };
	sprite = std::make_unique<Sprite>(textureRegion);
}

void WaterAreaRenderingSystem::Update(GameTime gameTime)
{
	for (int i = effects.size() - 1; i >= 0; i--)
	{
		effects[i].Update(gameTime);

		//if (effects[i].IsFinished())
		//	RemoveByValue(effects, &effects[i]);
	}
}

void WaterAreaRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	for (auto &effect : effects)
	{
		effect.Draw(spriteBatch);
	}
}
