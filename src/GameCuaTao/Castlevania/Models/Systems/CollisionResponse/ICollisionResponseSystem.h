#pragma once

namespace Castlevania
{
	struct ObjectCollection;

	class ICollisionResponseSystem
	{
	public:
		virtual void Update(ObjectCollection &objectCollection) = 0;
		virtual ~ICollisionResponseSystem() {}
	};
}