#pragma once

#include <map>
#include "AbstractReader.h"
#include "../Animation/Animation.h"

using SpriteDict = std::map<std::string, Sprite>;
using AnimationDict = std::map<std::string, Animation>;

class AnimationReader : public AbstractReader<AnimationDict>
{
public:
	std::shared_ptr<AnimationDict> Read(std::string filePath, ContentManager &contentManager) override;
};