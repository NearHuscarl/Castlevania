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

	auto rootNode = xmlDocument.child("GameContent");
	auto sprites = SpriteDict{};

	for (auto spriteNode : rootNode.child("Spritesheet").children("Sprite"))
	{
		auto sprite = ReadSprite(spriteNode);
		sprites[sprite.GetID()] = sprite;
	}

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

Sprite AnimationReader::ReadSprite(pugi::xml_node spriteNode)
{
	auto name = spriteNode.attribute("ID").as_string();

	auto left = int{};
	auto top = int{};
	auto right = int{};
	auto bottom = int{};

	left = spriteNode.child("SpriteFrame").attribute("Left").as_int();
	top = spriteNode.child("SpriteFrame").attribute("Top").as_int();
	right = spriteNode.child("SpriteFrame").attribute("Right").as_int();
	bottom = spriteNode.child("SpriteFrame").attribute("Bottom").as_int();
	auto spriteFrame = Rect{ left, top, right - left, bottom - top };

	left = spriteNode.child("SpriteBoundary").attribute("Left").as_int();
	top = spriteNode.child("SpriteBoundary").attribute("Top").as_int();
	right = spriteNode.child("SpriteBoundary").attribute("Right").as_int();
	bottom = spriteNode.child("SpriteBoundary").attribute("Bottom").as_int();
	auto spriteBoundary = Rect{ left, top, right - left, bottom - top };
	
	auto sprite = Sprite{};
	if (spriteBoundary == Rect::Empty())
		sprite = Sprite{ name, spriteFrame };
	else
		sprite = Sprite{ name, spriteFrame, spriteBoundary };
	
	return sprite;
}