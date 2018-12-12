#pragma once

#include "IControlSystem.h"

namespace Castlevania
{
	class ControlSystem : public IControlSystem
	{
	public:
		void Enabled(bool value) override;
		bool Enabled() override;

		virtual void Receive(int message) override {};
		virtual void Update(UpdateData &updateData) {};

	protected:
		bool enabled;
	};
}