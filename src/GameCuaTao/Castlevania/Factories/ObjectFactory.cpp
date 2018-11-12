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
	};
}

ObjectCollection ObjectFactory::CreateObjectCollection(ObjectsProperties objectsProperties)
{
	auto objectCollection = ObjectCollection{};

	for (auto properties : objectsProperties)
	{
		auto name = properties.at("name");

		if (BOUNDARIES.find(name) != BOUNDARIES.end())
		{
			auto x = std::stoi(properties.at("x"));
			auto y = std::stoi(properties.at("y"));
			auto width = std::stoi(properties.at("width"));
			auto height = std::stoi(properties.at("height"));
			auto trigger = Rect{ x, y - height, width, height };

			objectCollection.boundaries[name] = trigger;
		}
		else if (TRIGGERS.find(name) != TRIGGERS.end())
		{
			auto x = std::stoi(properties.at("x"));
			auto y = std::stoi(properties.at("y"));
			auto width = std::stoi(properties.at("width"));
			auto height = std::stoi(properties.at("height"));
			auto trigger = Rect{ x, y - height, width, height };
			
			objectCollection.triggers[name] = trigger;
		}
		else if (POSITIONS.find(name) != POSITIONS.end())
		{
			auto x = std::stof(properties.at("x"));
			auto y = std::stof(properties.at("y"));
			auto height = std::stoi(properties.at("height"));
			auto position = Vector2{ x, y - height };

			objectCollection.positions[name] = position;
		}
		else // GameObject (Simon, Bat, Skeleton...)
		{
			auto object = ConstructObject(name);
			auto x = std::stof(properties.at("x"));
			auto y = std::stof(properties.at("y"));
			auto height = std::stoi(properties.at("height"));

			object->SetPosition(x, y - height);
			objectCollection.entities.push_back(std::move(object));
		}
	}

	return objectCollection;
}

std::unique_ptr<GameObject> ObjectFactory::ConstructObject(std::string name)
{
	auto type = stringToType.at(name);
	
	switch (type)
	{
		case EntityType::Simon:
			return std::make_unique<Simon>();

		case EntityType::Player:
			return std::make_unique<Player>();

		case EntityType::Bat:
			return std::make_unique<Bat>();

		case EntityType::FirePit:
			return std::make_unique<FirePit>();

		default:
			throw std::invalid_argument("Object name is invalid");
	}
}
