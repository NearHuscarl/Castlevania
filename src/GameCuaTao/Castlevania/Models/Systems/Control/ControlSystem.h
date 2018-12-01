#pragma once

#include "IControlSystem.h"

namespace Castlevania
{
	class ControlSystem : public IControlSystem
	{
	public:
		void Enabled(bool value) override;

		virtual void Update() = 0;

	protected:
		bool enabled;
	};
}