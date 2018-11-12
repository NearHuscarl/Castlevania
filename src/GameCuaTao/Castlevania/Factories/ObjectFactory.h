#pragma once

#include "ObjectCollection.h"
#include "../Models/GameObject.h"
#include "../Models/EntityType.h"

namespace Castlevania
{
	using ObjectProperties = std::map<std::string, std::string>;
	using ObjectsProperties = std::vector<ObjectProperties>;

	class ObjectFactory
	{
	public:
		ObjectFactory();
		ObjectCollection CreateObjectCollection(ObjectsProperties properties);

	private:
		std::map<std::string, EntityType> stringToType;
		std::unique_ptr<GameObject> ConstructObject(std::string name);
	};
}