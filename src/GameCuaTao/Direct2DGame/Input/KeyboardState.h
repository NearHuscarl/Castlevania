#pragma once

constexpr auto KEYSTATE_BUFFER_SIZE = 256;

struct KeyboardState
{
public:
	KeyboardState(unsigned char *keyStates);

	bool IsKeyDown(int KeyCode);
	bool IsKeyUp(int KeyCode);

private:
	unsigned char keyStates[KEYSTATE_BUFFER_SIZE]; // DirectInput keyboard state buffer

	void InitializeKeyStates(unsigned char *keyStates);
	void InitializeEmptyKeyStates();
};