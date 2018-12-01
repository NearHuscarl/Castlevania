#pragma once

#include <map>
#include "RectangleObject.h"
#include "TriggerType.h"

namespace Castlevania
{
	class Trigger : public RectangleObject
	{
	public:
		Trigger(RectF boundingBox, TriggerType type);
		
		void AddProperty(std::string key, std::string value);
		std::string Property(std::string key);

		bool Enabled();
		void Enabled(bool value);

		TriggerType GetTriggerType();

	private:
		TriggerType type;
		bool enabled;
		std::map<std::string, std::string> properties;
	};
}