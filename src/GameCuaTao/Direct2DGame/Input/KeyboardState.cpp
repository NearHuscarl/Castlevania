#include "KeyboardState.h"

KeyboardState::KeyboardState(unsigned char *keyStates)
{
	if (keyStates == nullptr)
	{
		InitializeEmptyKeyStates();
	}
	else
	{
		InitializeKeyStates(keyStates);
	}
}

bool KeyboardState::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80);
}

bool KeyboardState::IsKeyUp(int KeyCode)
{
	return !(keyStates[KeyCode] & 0x80);
}

void KeyboardState::InitializeKeyStates(unsigned char *keyStates)
{
	for (auto i = 0; i < KEYSTATE_BUFFER_SIZE; i++)
	{
		this->keyStates[i] = keyStates[i];
	}
}

void KeyboardState::InitializeEmptyKeyStates()
{
	for (auto i = 0; i < KEYSTATE_BUFFER_SIZE; i++)
	{
		this->keyStates[i] = '\0';
	}
}
