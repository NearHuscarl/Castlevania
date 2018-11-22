#pragma once

#include <map>
#include "AbstractReader.h"
#include "../Extensions/Animations/AnimationFactory.h"

class AnimationFactoryReader : public AbstractReader<AnimationFactory>
{
public:
	std::shared_ptr<AnimationFactory> Read(std::string filePath, ContentManager &contentManager) override;
};