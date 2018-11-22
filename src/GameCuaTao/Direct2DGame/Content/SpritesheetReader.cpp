#include "Library/pugixml/pugixml.hpp"
#include "SpritesheetReader.h"
#include "LoadContentException.h"
#include "ContentManager.h"
#include "../Utilities/FileLogger.h"

std::shared_ptr<Spritesheet> SpritesheetReader::Read(std::string filePath, ContentManager &contentManager)
{
	auto xmlDocument = pugi::xml_document{};
	auto result = xmlDocument.load_file(filePath.c_str());

	if (!result)
	{
		FileLogger::GetInstance().Error("{}() failed: {}. Path: {}", __FUNCTION__, result.description(), filePath);
		throw LoadContentException(result.description());
	}

	auto rootNode = xmlDocument.child("GameContent");
	auto texturePath = std::string(rootNode.child("Spritesheet").attribute("TexturePath").as_string());
	auto resolvedTexturePath = contentManager.ResolvePath(Path{ filePath }.parent_path(), texturePath);
	auto texture = contentManager.Load<Texture>(resolvedTexturePath);
	auto spritesheet = std::make_shared<Spritesheet>();

	for (auto spriteNode : rootNode.child("Spritesheet").children("Sprite"))
	{
		auto name = spriteNode.attribute("ID").as_string();

		auto spriteFrame = Rect{
			spriteNode.child("SpriteFrame").attribute("Left").as_int(),
			spriteNode.child("SpriteFrame").attribute("Top").as_int(),
			spriteNode.child("SpriteFrame").attribute("Width").as_int(),
			spriteNode.child("SpriteFrame").attribute("Height").as_int(),
		};

		auto spriteBoundary = RectF{
			spriteNode.child("SpriteBoundary").attribute("Left").as_float(),
			spriteNode.child("SpriteBoundary").attribute("Top").as_float(),
			spriteNode.child("SpriteBoundary").attribute("Width").as_float(),
			spriteNode.child("SpriteBoundary").attribute("Height").as_float(),
		};

		if (spriteBoundary == RectF::Empty())
			spritesheet->emplace(name, TextureRegion{ texture, spriteFrame });
		else
			spritesheet->emplace(name, TextureRegion{ texture, spriteFrame, spriteBoundary });
	}

	return spritesheet;
}
