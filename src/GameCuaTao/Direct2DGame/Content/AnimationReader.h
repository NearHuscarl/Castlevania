#pragma once

#include <map>
#include "Library/pugixml/pugixml.hpp"
#include "AbstractReader.h"
#include "../Data/Animation.h"

using AnimationDict = std::map<std::string, Animation>;
using SpriteDict = std::map<std::string, Sprite>;

class AnimationReader : public AbstractReader<AnimationDict>
{
public:
	std::shared_ptr<AnimationDict> Read(std::string filePath, ContentManager &contentManager) override;

private:
	SpriteDict ReadSprites(pugi::xml_node rootNode);
};