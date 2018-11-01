#include "Library/pugixml/pugixml.hpp"
#include "AnimationReader.h"
#include "LoadContentException.h"
#include "ContentManager.h"
#include "../Utilities/FileLogger.h"

std::shared_ptr<AnimationDict> AnimationReader::Read(std::string filePath, ContentManager &contentManager)
{
	auto xmlDocument = pugi::xml_document{};
	auto result = xmlDocument.load_file(filePath.c_str());

	if (!result)
	{
		FileLogger::GetInstance().Error(result.description());
		throw LoadContentException(result.description());
	}

	auto rootDoc = xmlDocument.child("GameContent");
	auto sprites = SpriteDict{};
	auto left = int{}, top = int{}, right = int{}, bottom = int{};

	for (auto spriteNode : rootDoc.child("Spritesheet").children("Sprite"))
	{
		auto name = spriteNode.attribute("ID").as_string();

		left = spriteNode.child("SpriteFrame").attribute("Left").as_int();
		top = spriteNode.child("SpriteFrame").attribute("Top").as_int();
		right = spriteNode.child("SpriteFrame").attribute("Right").as_int();
		bottom = spriteNode.child("SpriteFrame").attribute("Bottom").as_int();
		auto spriteFrame = Rect{ left, top, right - left, bottom - top};

		left = spriteNode.child("SpriteBoundary").attribute("Left").as_int();
		top = spriteNode.child("SpriteBoundary").attribute("Top").as_int();
		right = spriteNode.child("SpriteBoundary").attribute("Right").as_int();
		bottom = spriteNode.child("SpriteBoundary").attribute("Bottom").as_int();
		auto spriteBoundary = Rect{ left, top, right - left, bottom - top };

		if (spriteBoundary == Rect::Empty())
			sprites[name] = Sprite{ name, spriteFrame };
		else
			sprites[name] = Sprite{ name, spriteFrame, spriteBoundary };
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
