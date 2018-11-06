#pragma once

#include <map>
#include "Library/pugixml/pugixml.hpp"
#include "AbstractReader.h"
#include "../Extensions/Animations/AnimationFactory.h"

using TextureRegionDict = std::map<std::string, TextureRegion>;

class AnimationFactoryReader : public AbstractReader<AnimationFactory>
{
public:
	std::shared_ptr<AnimationFactory> Read(std::string filePath, ContentManager &contentManager) override;

private:
	TextureRegionDict ReadTextureRegions(pugi::xml_node rootNode, std::shared_ptr<Texture> texture);
};