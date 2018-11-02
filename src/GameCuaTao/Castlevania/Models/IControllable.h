#pragma once

namespace Castlevania
{
	class IControllable
	{
	public:
		virtual void UpdateInput() = 0;
		virtual ~IControllable() {};
	};
}