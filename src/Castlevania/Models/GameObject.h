#pragma once

#include <map>
#include "States.h"
#include "../Animation/Animation.h"
#include "../Animation/AnimationSettings.h"

typedef std::map<std::string, Animation*> AnimationDict;

class GameObject
{
public:
	GameObject();

	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	
	virtual void SetState(int state) { this->state = state; }
	virtual int GetState() { return this->state; }

	virtual std::string GetAnimationState() { return ""; }

	virtual void LoadContent() {};

	virtual void Update(unsigned long deltaTime);
	virtual void Render();
	
	virtual ~GameObject();

protected:

	float x;
	float y;

	float vx;
	float vy;

	int nx;

	int state;

	AnimationDict animations;

	void InitAnimation(std::vector<std::string> animationIDs);
};