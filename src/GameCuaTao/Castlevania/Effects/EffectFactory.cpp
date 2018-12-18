#include "EffectFactory.h"
#include "SparkEffect.h"
#include "FlameEffect.h"
#include "BigFlameEffect.h"
#include "MoneyTextEffect.h"
#include "FlashingMoneyTextEffect.h"
#include "WaterEffect.h"

using namespace Castlevania;

EffectFactory::EffectFactory(ContentManager &content) : content{ content }
{
}

std::unique_ptr<IEffect> EffectFactory::CreateSparkEffect()
{
	auto sparkTexture = content.Load<Texture>("Effects/Spark.png");
	auto effect = std::make_unique<SparkEffect>(sparkTexture);

	return effect;
}

std::unique_ptr<IEffect> EffectFactory::CreateFlameEffect()
{
	// TODO: remove this
	auto flameAnimations = content.Load<AnimationFactory>("Effects/Flame.ani.xml");
	auto effect = std::make_unique<FlameEffect>(flameAnimations);

	return effect;
}

std::unique_ptr<IEffect> EffectFactory::CreateBigFlameEffect()
{
	auto flameAnimations = content.Load<AnimationFactory>("Effects/Flame.ani.xml");
	auto effect = std::make_unique<BigFlameEffect>(flameAnimations);

	return effect;
}

std::unique_ptr<IEffect> EffectFactory::CreateMoneyTextEffect(int money)
{
	auto moneyTextTexture = std::shared_ptr<Texture>{};
	auto effect = std::unique_ptr<MoneyTextEffect>{};

	switch (money)
	{
		case 100:
			moneyTextTexture = content.Load<Texture>("Effects/100.png");
			effect = std::make_unique<MoneyTextEffect>(moneyTextTexture);
			break;

		case 400:
			moneyTextTexture = content.Load<Texture>("Effects/400.png");
			effect = std::make_unique<MoneyTextEffect>(moneyTextTexture);
			break;

		case 700:
			moneyTextTexture = content.Load<Texture>("Effects/700.png");
			effect = std::make_unique<MoneyTextEffect>(moneyTextTexture);
			break;
	}

	return effect;
}

std::unique_ptr<IEffect> EffectFactory::CreateFlashingMoneyTextEffect()
{
	auto moneyTextAnimation = content.Load<AnimationFactory>("Effects/1000.ani.xml");
	auto effect = std::make_unique<FlashingMoneyTextEffect>(moneyTextAnimation);

	return effect;
}

std::unique_ptr<IEffect> EffectFactory::CreateWaterEffect()
{
	auto waterTexture = content.Load<Texture>("Effects/Water.png");
	auto effect = std::make_unique<WaterEffect>(waterTexture);

	return effect;
}
