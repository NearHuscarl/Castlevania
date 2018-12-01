#include "Trigger.h"

using namespace Castlevania;

Trigger::Trigger(RectF rect, TriggerType type) : RectangleObject{ rect, EntityType::Trigger }
{
	this->type = type;
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
