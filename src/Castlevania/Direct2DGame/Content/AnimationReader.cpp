#include <memory>
#include <map>
#include "Library/pugixml.hpp"
#include "AnimationReader.h"
#include "LoadContentException.h"
#include "ContentManager.h"

std::shared_ptr<AnimationDict> AnimationReader::Read(std::string filePath, ContentManager &contentManager)
{
	pugi::xml_document animationsDoc;
	pugi::xml_parse_result result = animationsDoc.load_file(filePath.c_str());

	if (!result)
		throw LoadContentException(result.description());

	pugi::xml_node rootDoc = animationsDoc.child("root");
	SpriteDict sprites;
	
	for (auto spriteNode : rootDoc.child("Spritesheet").children("Sprite"))
	{
		std::string name = spriteNode.attribute("Name").as_string();
		int left = spriteNode.attribute("Left").as_int();
		int top = spriteNode.attribute("Top").as_int();
		int right = spriteNode.attribute("Right").as_int();
		int bottom = spriteNode.attribute("Bottom").as_int();

		Sprite sprite = Sprite(name, BoundingBox(left, top, right, bottom));

		sprites[name] = sprite;
	}

	std::string texturePath = rootDoc.child("Spritesheet").attribute("TexturePath").as_string();
	auto texture = contentManager.Load<Texture>(texturePath);
	AnimationDict animations;

	for (auto animationNode : rootDoc.child("Animations").children("Animation"))
	{
		int defaultAnimateTime = animationNode.attribute("DefaultTime").as_int();
		Animation animation = Animation(texture, defaultAnimateTime);

		for (auto frameNode : animationNode.children("Frame"))
		{
			std::string name = frameNode.attribute("Name").as_string();
			animation.Add(sprites[name]);
		}

		std::string name = animationNode.attribute("Name").as_string();
		animations[name] = animation;
	}

	return std::make_shared<AnimationDict>(animations);
}
