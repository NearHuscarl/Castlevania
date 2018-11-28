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