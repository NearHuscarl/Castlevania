#pragma once

namespace Castlevania
{
	enum class EntityType
	{
		Boundary,
		Position,
		Trigger,
		Player,

		Bat,
		Cloud,
		FirePit,

		// Weapons
		Whip,
		Knife,

		// Items
		Heart,
		WhipPowerup,
		KnifeItem,
		MoneyBag,
		
		Unknown,
	};
}