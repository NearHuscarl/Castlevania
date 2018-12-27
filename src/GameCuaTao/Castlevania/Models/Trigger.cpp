#include "Trigger.h"

using namespace Castlevania;

Trigger::Trigger(TriggerType type) : GameObject{ ObjectId::Trigger }
{
	this->type = type;
}

void Trigger::AddProperty(std::string key, std::string value)
{
	properties[key] = value;
}

std::string Trigger::Property(std::string key)
{
	return properties.at(key);
}

TriggerType Trigger::GetTriggerType()
{
	return type;
}
