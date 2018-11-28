#pragma once

namespace Castlevania
{
	enum class EntityType
	{
		Boundary,
		Position,
		Trigger,
		SpawnArea,
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

		// Misc
		Castle,
		DirtBlock,

		Unknown,
	};
}