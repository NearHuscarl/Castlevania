#include "ObjectFactory.h"
#include "../Models/Characters/Simon.h"
#include "../Models/Characters/Player.h"
#include "../Models/Characters/Bat.h"
#include "../Models/Items/FirePit.h"

using namespace Castlevania;

ObjectFactory::ObjectFactory()
{
	stringToType =
	{
		{ "Simon", EntityType::Simon },
		{ "Player", EntityType::Player },
		{ "Bat", EntityType::Bat },
		{ "Cloud", EntityType::Cloud },
		{ "FirePit", EntityType::FirePit },
		{ "Ground", EntityType::Boundary },
		{ "LeftBorder", EntityType::Boundary },
		{ "RightBorder", EntityType::Boundary },
		{ "EntryTrigger", EntityType::Boundary }, // TODO:
	};
}

std::unique_ptr<GameObject> ObjectFactory::CreateObject(ObjectProperties properties)
{
	auto name = properties.at("name");
	auto object = ConstructObject(name);

	auto x = std::stof(properties.at("x"));
	auto y = std::stof(properties.at("y"));
	object->SetPosition(x, y);

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::ConstructObject(std::string name)
{
	auto type = stringToType.at(name);
	
	switch (type)
	{
		case EntityType::Simon:
			return std::make_unique<Simon>();
			break;

		case EntityType::Player:
			return std::make_unique<Player>();
			break;

		case EntityType::Bat:
			return std::make_unique<Bat>();
			break;

		case EntityType::FirePit:
			return std::make_unique<FirePit>(); // TODO:
			break;

		case EntityType::Boundary:
			return std::make_unique<Bat>(); // TODO:
			break;

		default:
			throw std::invalid_argument("Object name is invalid");
	}
}
