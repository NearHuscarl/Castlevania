#include <memory>
#include <map>
#include "Library/pugixml/pugixml.hpp"
#include "AnimationReader.h"
#include "LoadContentException.h"
#include "ContentManager.h"
#include "../Utilities/FileLogger.h"

std::shared_ptr<AnimationDict> AnimationReader::Read(std::string filePath, ContentManager &contentManager)
{
	auto animationsDoc = pugi::xml_document{};
	auto result = animationsDoc.load_file(filePath.c_str());

	if (!result)
	{
		FileLogger::GetInstance().Error(result.description());
		throw LoadContentException(result.description());
	}

	auto rootDoc = animationsDoc.child("root");
	auto sprites = SpriteDict{};
	
	for (auto spriteNode : rootDoc.child("Spritesheet").children("Sprite"))
	{
		auto name = spriteNode.attribute("ID").as_string();
		auto left = spriteNode.attribute("Left").as_int();
		auto top = spriteNode.attribute("Top").as_int();
		auto right = spriteNode.attribute("Right").as_int();
		auto bottom = spriteNode.attribute("Bottom").as_int();

		auto sprite = Sprite{ name, Rect(left, top, right, bottom) };

		sprites[name] = sprite;
	}

	auto texturePath = rootDoc.child("Spritesheet").attribute("TexturePath").as_string();
	auto texture = contentManager.Load<Texture>(texturePath);
	auto animations = AnimationDict{};

	for (auto animationNode : rootDoc.child("Animations").children("Animation"))
	{
		auto defaultAnimateTime = animationNode.attribute("DefaultTime").as_uint();
		auto animation = Animation{ texture, defaultAnimateTime };

		for (auto frameNode : animationNode.children("Frame"))
		{
			auto name = frameNode.attribute("SpriteID").as_string();
			animation.Add(sprites[name]);
		}

		auto name = animationNode.attribute("Name").as_string();
		animations[name] = animation;
	}

	return std::make_shared<AnimationDict>(animations);
}
