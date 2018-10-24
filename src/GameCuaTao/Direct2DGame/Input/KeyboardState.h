#pragma once

constexpr auto KEYSTATE_BUFFER_SIZE = 256;

struct KeyboardState
{
public:
	KeyboardState(unsigned char *keyStates)
	{
		if (keyStates == nullptr)
			return;

		for (auto i = 0; i < KEYSTATE_BUFFER_SIZE; i++)
		{
			this->keyStates[i] = keyStates[i];
		}
	}

	bool IsKeyDown(int KeyCode)
	{
		return (keyStates[KeyCode] & 0x80) > 0;
	}

	bool IsKeyUp(int KeyCode)
	{
		return (keyStates[KeyCode] & 0x80) <= 0;
	}

private:
	unsigned char keyStates[KEYSTATE_BUFFER_SIZE]; // DirectInput keyboard state buffer 
};