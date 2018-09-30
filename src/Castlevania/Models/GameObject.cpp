#include <d3dx9.h>

#include "GameObject.h"
#include "../Utilities/Debug.h"
#include "../Game.h"
#include "../Animation/AnimationManager.h"

vector<Animation*> GameObject::animations;

GameObject::GameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
}

void GameObject::Update(DWORD dt)
{
	x += vx*dt;
	y += vy*dt;
}

void GameObject::Render()
{
}

void GameObject::AddAnimation(int aniId)
{
	Animation *ani = AnimationManager::GetInstance()->Get(aniId);
	animations.push_back(ani);
}

GameObject::~GameObject()
{
}