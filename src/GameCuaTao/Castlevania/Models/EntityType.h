#pragma once

namespace Castlevania
{
	enum class EntityType
	{
		Boundary,
		Position,
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
		
		Unknown,
	};
}