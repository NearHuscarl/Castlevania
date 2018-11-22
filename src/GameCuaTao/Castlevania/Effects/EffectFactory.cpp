#include "EffectFactory.h"
#include "FlameEffect.h"

using namespace Castlevania;

EffectFactory::EffectFactory(ContentManager &content) : content{ content }
{
}

std::unique_ptr<IEffect> EffectFactory::CreateFlameEffect()
{
	auto sparkTexture = content.Load<Texture>("Effects/Spark.png");
	auto flameAnimations = content.Load<AnimationFactory>("Effects/Flame.ani.xml");
	auto flameEffect = std::make_unique<FlameEffect>(sparkTexture, flameAnimations);

	return flameEffect;
}
