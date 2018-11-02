#include "Bat.h"

using namespace Castlevania;

void Bat::LoadContent(ContentManager &content)
{
	animations = content.Load<AnimationDict>("Characters/NPCs/BatAnimationDef.xml");
	currentAnimation = "fly";
}

void Bat::Update(float deltaTime)
{
	GetAnimation().Update();
}

void Bat::Draw(SpriteBatch &spritebatch)
{
	GetAnimation().Draw(spritebatch, position, Color::White(), SpriteEffects::None);
}