#include "EntityRenderingSystem.h"

using namespace Castlevania;

EntityRenderingSystem::EntityRenderingSystem(GameObject &parent, std::string spriteConfigPath, std::unique_ptr<IEffect> effect)
	: EffectRenderingSystem{ spriteConfigPath, std::move(effect) }, parent{ parent }
{
}

GameObject &EntityRenderingSystem::GetParent()
{
	return parent;
}
