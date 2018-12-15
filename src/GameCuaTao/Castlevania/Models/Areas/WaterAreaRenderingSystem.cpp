#include "WaterAreaRenderingSystem.h"
#include "../../Utilities/CppExtensions.h"
#include "../GameObject.h"
#include "../Settings.h"

using namespace Castlevania;

WaterAreaRenderingSystem::WaterAreaRenderingSystem(WaterArea &parent, RectF boundingBox, EffectFactory &effectFactory) :
	parent{ parent },
	effectFactory{ effectFactory }
{
	this->boundingBox = boundingBox;
}

Sprite &WaterAreaRenderingSystem::GetSprite()
{
	return *sprite;
}

GameObject &WaterAreaRenderingSystem::GetParent()
{
	return parent;
}

void WaterAreaRenderingSystem::Receive(int message)
{
	switch (message)
	{
		case OBJECT_HITS_WATER_SURFACE:
		{
			auto effect = effectFactory.CreateWaterEffect();
			
			effect->Show(parent.splashPosition);
			effects.push_back(std::move(effect));
			break;
		}
	}
}

void WaterAreaRenderingSystem::LoadContent(ContentManager &content)
{
	RenderingSystem::LoadContent(content);

	auto textureRegion = TextureRegion{ bboxTexture, (Rect)boundingBox };
	sprite = std::make_unique<Sprite>(textureRegion);
}

void WaterAreaRenderingSystem::Update(GameTime gameTime)
{
	for (int i = effects.size() - 1; i >= 0; i--)
	{
		auto effect = effects[i];

		effect->Update(gameTime);

		if (effects[i]->IsFinished())
			RemoveByValue(effects, effect);
	}
}

void WaterAreaRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	RenderingSystem::Draw(spriteBatch);

	for (auto &effect : effects)
	{
		effect->Draw(spriteBatch);
	}
}
