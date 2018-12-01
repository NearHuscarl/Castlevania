#pragma once

#include "RectangleObject.h"
#include "TriggerType.h"

namespace Castlevania
{
	class Trigger : public RectangleObject
	{
	public:
		Trigger(RectF boundingBox, TriggerType type);
		
		bool Enabled();
		void Enabled(bool value);
		TriggerType GetTriggerType();

	private:
		TriggerType type;
		bool enabled;
	};
}