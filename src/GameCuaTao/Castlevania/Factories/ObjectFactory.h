#pragma once

#include "ObjectCollection.h"
#include "../Models/GameObject.h"
#include "../Models/EntityType.h"
#include "../Models/Characters/Player/Player.h"

namespace Castlevania
{
	using ObjectProperties = std::map<std::string, std::string>;
	using ObjectsProperties = std::vector<ObjectProperties>;

	class ObjectFactory
	{
	public:
		ObjectFactory();

		ObjectCollection CreateObjectCollection(ObjectsProperties properties);
		
		std::unique_ptr<Player> CreatePlayer();
		std::unique_ptr<Player> CreateSimon();

	private:
		std::map<std::string, EntityType> stringToType;
		std::unique_ptr<GameObject> ConstructObject(std::string name);
	};
}