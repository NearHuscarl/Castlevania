#pragma once

#include <map>
#include "Animation.h"
#include "SpriteManager.h"
#include "../ContentManager.h"

using AnimationDict = std::map<std::string, Animation*>;

class AnimationManager
{
public:
	static AnimationManager *GetInstance();
	
	void LoadResource(ContentManager *content);
	void AddSprite(std::string spriteID, BoundingBox boundingBox, IDirect3DTexture9 *texture);
	void AddAnimation(std::string animationID, int animateTime, std::vector<std::string> sprites);
	Animation *GetAnimation(std::string animationID);

private:
	static AnimationManager *instance;
	AnimationDict animations;
};