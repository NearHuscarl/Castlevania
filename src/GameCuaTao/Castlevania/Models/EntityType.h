#pragma once

namespace Castlevania
{
	enum class EntityType
	{
		Boundary,
		Position,
		Trigger,
		Player,
		SpawnPoint,

		// Areas
		SpawnArea,
		ViewportArea,

		// Intro objects
		Bat,
		Cloud,

		// Containers
		Brazier,
		Candle,

		// Enemies
		Zombie,
		Panther,
		Fishman,
		VampireBat,
		GiantBat, // first boss

		// Weapons
		Axe,
		Dagger,
		Boomerang,
		Fireball, // from Fishman
		Whip,

		// Items
		DoubleShot,
		TripleShot,
		
		MoneyBag,
		PorkChop,

		AxeItem,
		BoomerangItem,
		Cross,
		DaggerItem,
		HolyWater,
		LargeHeart,
		SmallHeart,
		InvisibleJar,
		StopWatch,
		WhipPowerup,
		CrystalBall,

		// Misc
		Door,
		BreakableWall,
		Castle,
		DirtBlock,

		Unknown,
	};
}