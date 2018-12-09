#pragma once

namespace Castlevania
{
	enum class EntityType
	{
		Area,
		Boundary,
		Position,
		Trigger,
		SpawnArea,
		SpawnPoint,
		Player,

		BreakableWall,

		// Intro objects
		Bat,
		Cloud,

		// Courtyard objects
		Brazier,

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
		Castle,
		DirtBlock,

		Unknown,
	};
}