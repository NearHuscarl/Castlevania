#pragma once

namespace Castlevania
{
	struct ObjectCollection;

	class ICollisionSystem
	{
	public:
		virtual void Update(ObjectCollection &objectCollection) = 0;
	};
}