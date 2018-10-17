#pragma once

#include <map>
#include "Direct2DGame/Base/Vector.h"
#include "Direct2DGame/Animation/Animation.h"
#include "Direct2DGame/Content/ContentManager.h"

class GameObject
{
public:
	GameObject();

	void SetPosition(float x, float y);
	void SetSpeed(float vx, float vy);
	
	virtual void SetState(int state);
	virtual int GetState();

	virtual std::string GetAnimationState() { return ""; }

	virtual void LoadContent(ContentManager &content) = 0;

	virtual void Update(unsigned long deltaTime);
	virtual void Draw(ISpriteHandler_ spriteHandler);
	
	virtual ~GameObject();

protected:
	Vector position;
	Vector velocity;

	int direction;

	int state;

	std::shared_ptr<AnimationDict> animations;
};