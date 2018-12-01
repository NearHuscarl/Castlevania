#include "Trigger.h"

using namespace Castlevania;

Trigger::Trigger(RectF rect, TriggerType type) : RectangleObject{ rect, EntityType::Trigger }
{
	this->type = type;
	this->enabled = true;
}

void Trigger::AddProperty(std::string key, std::string value)
{
	properties[key] = value;
}

std::string Trigger::Property(std::string key)
{
	return properties.at(key);
}

bool Trigger::Enabled()
{
	return enabled;
}

void Trigger::Enabled(bool value)
{
	enabled = value;
}

TriggerType Trigger::GetTriggerType()
{
	return type;
}
