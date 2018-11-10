#pragma once

#include "../Models/GameObject.h"
#include "../Models/EntityType.h"

namespace Castlevania
{
	using ObjectProperties = std::map<std::string, std::string>;

	class ObjectFactory
	{
	public:
		ObjectFactory();
		std::unique_ptr<GameObject> CreateObject(ObjectProperties properties);

	private:
		std::map<std::string, EntityType> stringToType;
		std::unique_ptr<GameObject> ConstructObject(std::string name);
	};
}