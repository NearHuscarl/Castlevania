#pragma once

#include <map>
#include "Library/pugixml/pugixml.hpp"
#include "AbstractReader.h"
#include "../Animations/AnimationSet.h"

using AnimationDict = std::map<std::string, Animation>;
using SpriteDict = std::map<std::string, Sprite>;

class AnimationSetReader : public AbstractReader<AnimationSet>
{
public:
	std::shared_ptr<AnimationSet> Read(std::string filePath, ContentManager &contentManager) override;

private:
	SpriteDict ReadSprites(pugi::xml_node rootNode);
};