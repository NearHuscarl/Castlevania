#include "Library/pugixml/pugixml.hpp"
#include "AnimationFactoryReader.h"
#include "LoadContentException.h"
#include "ContentManager.h"
#include "../Utilities/FileLogger.h"

std::shared_ptr<AnimationFactory> AnimationFactoryReader::Read(std::string filePath, ContentManager &contentManager)
{
	auto xmlDocument = pugi::xml_document{};
	auto result = xmlDocument.load_file(filePath.c_str());

	if (!result)
	{
		FileLogger::GetInstance().Error("{}() failed: {}. Path: {}", __FUNCTION__, result.description(), filePath);
		throw LoadContentException(result.description());
	}

	auto rootNode = xmlDocument.child("GameContent");
	auto atlasPath = rootNode.child("Animations").attribute("AtlasPath").as_string();
	auto resolvedAtlasPath = contentManager.ResolvePath(Path{ filePath }.parent_path(), atlasPath);
	auto spritesheet = contentManager.Load<Spritesheet>(resolvedAtlasPath);
	auto animations = AnimationDict{};

	for (auto animationNode : rootNode.child("Animations").children("Animation"))
	{
		auto name = animationNode.attribute("Name").as_string();
		auto defaultAnimateTime = animationNode.attribute("DefaultTime").as_int();
		auto isLooping = animationNode.attribute("IsLooping").as_bool();
		auto animation = Animation{ name, defaultAnimateTime, isLooping };

		for (auto frameNode : animationNode.children("Frame"))
		{
			auto name = frameNode.attribute("SpriteID").as_string();
			auto time = frameNode.attribute("Time").as_int(); // equals to 0 if Time attribute not found
			animation.Add(spritesheet->at(name), time);
		}

		animations.emplace(name, animation);
	}

	return std::make_shared<AnimationFactory>(animations);
}
