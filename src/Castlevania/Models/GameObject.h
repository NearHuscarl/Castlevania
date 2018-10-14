#pragma once

#include <map>
#include "States.h"
#include "../Base/Vector.h"
#include "../Animation/Animation.h"
#include "../Animation/AnimationSettings.h"
#include "../Content/ContentManager.h"

class GameObject
{
public:
	GameObject();

	void SetPosition(float x, float y);
	void SetSpeed(float vx, float vy);
	
	virtual void SetState(int state) { this->state = state; }
	virtual int GetState() { return this->state; }

	virtual std::string GetAnimationState() { return ""; }

	virtual void LoadContent(ContentManager &content) = 0;

	virtual void Update(unsigned long deltaTime);
	virtual void Draw(SpritePtr spriteHandler);
	
	virtual ~GameObject();

protected:
	Vector position;
	Vector velocity;

	int direction;

	int state;

	std::shared_ptr<AnimationDict> animations;
};