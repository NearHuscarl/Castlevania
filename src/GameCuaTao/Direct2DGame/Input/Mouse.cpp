#include "Mouse.h"
#include "../Utilities/FileLogger.h"

InputDevice_ Mouse::inputDevice;

void Mouse::Initialize()
{
	auto input = DirectInput::GetInput();
	auto handle = DirectInput::GetHandle();
	auto result = input->CreateDevice(GUID_SysMouse, &inputDevice, nullptr);

	if (result != DI_OK)
	{
		FileLogger::GetInstance().Error("{}(): CreateDevice failed!", __FUNCTION__);
		return;
	}

	inputDevice->SetDataFormat(&c_dfDIMouse);
	inputDevice->SetCooperativeLevel(handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	inputDevice->Acquire();
	//d3ddev->ShowCursor(false);

	if (result != DI_OK)
		FileLogger::GetInstance().Error("{}(): DINPUT8::Acquire failed!", __FUNCTION__);
	else
		FileLogger::GetInstance().Info("Mouse has been initialized successfully");
}

MouseState Mouse::GetState()
{
	auto state = DIMOUSESTATE{};
	auto result = inputDevice->GetDeviceState(sizeof(state), (LPVOID)&state);

	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			result = inputDevice->Acquire();

			if (result == DI_OK)
				FileLogger::GetInstance().Info("Mouse re-acquired!");

			return MouseState{};
		}
		else
		{
			FileLogger::GetInstance().Error("{}(): DINPUT::GetDeviceState failed: {}", __FUNCTION__, result);
			return MouseState{};
		}
	}

	// Retrieve mouse position in game window
	auto mouseState = MouseState{ state };
	auto mousePosition = POINT{};
	auto handle = DirectInput::GetHandle();

	GetCursorPos(&mousePosition);
	ScreenToClient(handle, &mousePosition);

	mouseState.x = (float)mousePosition.x;
	mouseState.y = (float)mousePosition.y;
	mouseState.scrollWheelValue = state.lZ;

	return mouseState;
}

void Mouse::Release()
{
	if (inputDevice != nullptr)
	{
		inputDevice->Unacquire();
		inputDevice->Release();
		inputDevice = nullptr;
	}
}
