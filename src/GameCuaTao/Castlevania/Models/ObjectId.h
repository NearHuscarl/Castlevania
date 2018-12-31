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
		BreakableBlock,
		BreakableWall,

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
		RedMoneyBag,
		BlueMoneyBag,
		WhiteMoneyBag,
		FlashingMoneyBag,

		AxeItem,
		BoomerangItem,
		Cross,
		DaggerItem,
		HolyWaterItem,
		LargeHeart,
		SmallHeart,
		InvisibleJar,
		PorkChop,
		Stopwatch,
		WhipPowerup,

		DoubleShot,
		TripleShot,
		CrystalBall,

		// Misc
		Door,
		Castle,
		BrickBlock,
		DirtBlock,

		Unknown,
	};
}