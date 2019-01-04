#pragma once

#include <memory>
#include <string>
#include "Items/Powerup.h"

namespace Castlevania
{
	class ObjectFactory;

	class PowerupGenerator
	{
	public:
		PowerupGenerator(ObjectFactory &objectFactory);

		std::unique_ptr<Powerup> Generate();
		std::unique_ptr<Powerup> Generate(ObjectId powerupId);

	private:
		ObjectFactory &objectFactory;

		std::string GetGroup(ObjectId powerupType);
		ObjectId GetRandomPowerupType(const std::string &rarity);
	};
}