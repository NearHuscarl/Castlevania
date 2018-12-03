#include "EntityRenderingSystem.h"
#include "../../GameObject.h"
#include "../../Settings.h"

using namespace Castlevania;

EntityRenderingSystem::EntityRenderingSystem(
	GameObject &parent,
	std::string spriteConfigPath,
	std::unique_ptr<IEffect> effect)
	:
	AnimationRenderingSystem{ parent, spriteConfigPath }
{
	hitEffect = std::move(effect);
}

void EntityRenderingSystem::Receive(int message)
{
	switch (message)
	{
		case STATE_CHANGED:
			if (parent.GetState() == ObjectState::DYING)
				hitEffect->Show(parent.GetOriginPosition());
			break;
	}
}

void EntityRenderingSystem::Update(GameTime gameTime)
{
	switch (parent.GetState())
	{
		case ObjectState::NORMAL:
			sprite->Update();
			break;

		case ObjectState::DYING:
			if (hitEffect->IsFinished())
				parent.Destroy();
			break;
	}
}

void EntityRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	switch (parent.GetState())
	{
		case ObjectState::NORMAL:
			AnimationRenderingSystem::Draw(spriteBatch);
			break;

		case ObjectState::DYING:
			hitEffect->Draw(spriteBatch);
			break;
	}
}