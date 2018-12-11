#pragma once

#include "../GameObject.h"

namespace Castlevania
{
	enum class DoorState
	{
		NORMAL,
		OPENING,
		CLOSING,
	};

	class Door : public GameObject
	{
	public:
		Door();

		DoorState GetDoorState();
		void Idle();
		void Open();
		void Close();

	private:
		DoorState doorState;
	};
}