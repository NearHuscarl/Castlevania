#include "Trigger.h"

using namespace Castlevania;

Trigger::Trigger(RectF rect, TriggerType type) : RectangleObject{ rect, EntityType::Trigger }
{
	this->type = type;
}

TriggerType Trigger::GetTriggerType()
{
	return type;
}
