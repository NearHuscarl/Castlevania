#include "AnimationSetReader.h"
#include "LoadContentException.h"
#include "ContentManager.h"
#include "../Utilities/FileLogger.h"

std::shared_ptr<AnimationSet> AnimationSetReader::Read(std::string filePath, ContentManager &contentManager)
{
	auto xmlDocument = pugi::xml_document{};
	auto result = xmlDocument.load_file(filePath.c_str());

	if (!result)
	{
		FileLogger::GetInstance().Error(result.description());
		throw LoadContentException(result.description());
	}

	auto rootNode = xmlDocument.child("GameContent");
	auto sprites = ReadSprites(rootNode);
	auto texturePath = std::string(rootNode.child("Spritesheet").attribute("TexturePath").as_string());
	auto fullPath = (Path{ contentManager.GetRootDirectory() } / texturePath).string();
	
	if (!std::filesystem::exists(fullPath)) // fallback to the same directory as animationDef xml file if path not found
	{
		fullPath = (Path{ filePath }.parent_path() / texturePath).string();
		texturePath = std::filesystem::relative(Path{ fullPath }, contentManager.GetRootDirectory()).string();
	}

	auto texture = contentManager.Load<Texture>(texturePath);
	auto animations = AnimationDict{};

	for (auto animationNode : rootNode.child("Animations").children("Animation"))
	{
		auto name = animationNode.attribute("Name").as_string();
		auto defaultAnimateTime = animationNode.attribute("DefaultTime").as_int();
		auto isLooping = animationNode.attribute("IsLooping").as_bool();
		auto animation = Animation{ name, texture, defaultAnimateTime, isLooping };

		for (auto frameNode : animationNode.children("Frame"))
		{
			auto name = frameNode.attribute("SpriteID").as_string();
			animation.Add(sprites[name]);
		}

		animations[name] = animation;
	}

	return std::make_shared<AnimationSet>(animations);
}

SpriteDict AnimationSetReader::ReadSprites(pugi::xml_node rootNode)
{
	auto sprites = SpriteDict{};

	for (auto spriteNode : rootNode.child("Spritesheet").children("Sprite"))
	{
		auto name = spriteNode.attribute("ID").as_string();

		auto left = int{};
		auto top = int{};
		auto width = int{};
		auto height = int{};

		left = spriteNode.child("SpriteFrame").attribute("Left").as_int();
		top = spriteNode.child("SpriteFrame").attribute("Top").as_int();
		width = spriteNode.child("SpriteFrame").attribute("Width").as_int();
		height = spriteNode.child("SpriteFrame").attribute("Height").as_int();
		auto spriteFrame = Rect{ left, top, width, height };

		left = spriteNode.child("SpriteBoundary").attribute("Left").as_int();
		top = spriteNode.child("SpriteBoundary").attribute("Top").as_int();
		width = spriteNode.child("SpriteBoundary").attribute("Width").as_int();
		height = spriteNode.child("SpriteBoundary").attribute("Height").as_int();
		auto spriteBoundary = Rect{ left, top, width, height };

		auto sprite = Sprite{};
		if (spriteBoundary == Rect::Empty())
			sprite = Sprite{ name, spriteFrame };
		else
			sprite = Sprite{ name, spriteFrame, spriteBoundary };
		
		sprites[sprite.GetID()] = sprite;
	}

	return sprites;
}