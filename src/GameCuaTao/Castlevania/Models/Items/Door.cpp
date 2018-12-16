#include "Door.h"
#include "../Settings.h"

using namespace Castlevania;

Door::Door() : GameObject{ ObjectId::Door }
{
}

DoorState Door::GetDoorState()
{
	return doorState;
}

void Door::Idle()
{
	doorState = DoorState::NORMAL;
	SendMessageToSystems(MOVE_STATE_CHANGED);
}

void Door::Open()
{
	doorState = DoorState::OPENING;
	SendMessageToSystems(MOVE_STATE_CHANGED);
}

void Door::Close()
{
	doorState = DoorState::CLOSING;
	SendMessageToSystems(MOVE_STATE_CHANGED);
}
