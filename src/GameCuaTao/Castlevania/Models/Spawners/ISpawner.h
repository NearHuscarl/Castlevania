#pragma once

namespace Castlevania
{
	enum class SpawnState
	{
		ACTIVE,
		INACTIVE,
		SPAWNING,
	};

	class ISpawner
	{
	public:
		virtual SpawnState GetSpawnState() = 0;
		virtual void Activate() = 0;
		virtual void Deactivate() = 0;
	};
}