#pragma once

constexpr auto KEYSTATE_BUFFER_SIZE = 256;

struct KeyboardState
{
public:
	KeyboardState(unsigned char *keyStates)
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

	bool IsKeyDown(int KeyCode)
	{
		return (keyStates[KeyCode] & 0x80);
	}

	bool IsKeyUp(int KeyCode)
	{
		return !(keyStates[KeyCode] & 0x80);
	}

private:
	unsigned char keyStates[KEYSTATE_BUFFER_SIZE]; // DirectInput keyboard state buffer

	void InitializeKeyStates(unsigned char *keyStates)
	{
		for (auto i = 0; i < KEYSTATE_BUFFER_SIZE; i++)
		{
			this->keyStates[i] = keyStates[i];
		}
	}

	void InitializeEmptyKeyStates()
	{
		for (auto i = 0; i < KEYSTATE_BUFFER_SIZE; i++)
		{
			this->keyStates[i] = '\0';
		}
	}
};