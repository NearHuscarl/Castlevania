#pragma once

namespace Castlevania
{
	enum class ObjectId
	{
		Boundary,
		Position,
		Trigger,
		Player,
		SpawnPoint,

		// Areas
		SpawnArea,
		StageArea,
		BossFightArea,
		WaterArea,

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
		HolyWater,
		Boomerang,
		Fireball, // from Fishman
		Whip,

		// Items
		DoubleShot,
		TripleShot,
		
		RedMoneyBag,
		BlueMoneyBag,
		WhiteMoneyBag,
		FlashingMoneyBag,
		PorkChop,

		AxeItem,
		BoomerangItem,
		Cross,
		DaggerItem,
		HolyWaterItem,
		LargeHeart,
		SmallHeart,
		InvisibleJar,
		Stopwatch,
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