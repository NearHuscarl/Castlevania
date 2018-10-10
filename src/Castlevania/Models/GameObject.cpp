#include <d3dx9.h>

#include "GameObject.h"
#include "../Animation/AnimationManager.h"

GameObject::GameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
}

void GameObject::InitAnimation(std::vector<std::string> animationIDs)
{
	AnimationManager *animationMananger = AnimationManager::GetInstance();

	for (auto animationID : animationIDs)
	{
		animations[animationID] = animationMananger->GetAnimation(animationID);
	}
}

void GameObject::Update(unsigned long deltaTime)
{
	x += vx * deltaTime;
	y += vy * deltaTime;
}

void GameObject::Draw(ID3DXSprite *spriteHandler)
{
}

GameObject::~GameObject()
{
}