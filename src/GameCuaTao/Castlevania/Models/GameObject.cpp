#include "GameObject.h"

using namespace Castlevania;

void GameObject::SetState(int state)
{
	this->state = state;
}

int GameObject::GetState()
{
	return state;
}