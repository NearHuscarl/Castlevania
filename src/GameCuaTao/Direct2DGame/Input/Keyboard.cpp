#include "Keyboard.h"
#include "../Utilities/FileLogger.h"

IController *Keyboard::controller = nullptr;
InputDevice_ Keyboard::inputDevice;

Keyboard::Keyboard()
{
	inputDevice = nullptr;
}

void Keyboard::Initialize()
{
	auto input = DirectInput::GetInput();
	auto handle = DirectInput::GetHandle();
	auto result = input->CreateDevice(GUID_SysKeyboard, &inputDevice, nullptr);

	// TO-DO: put in exception handling
	if (result != DI_OK)
	{
		FileLogger::GetInstance().Error("{}(): CreateDevice failed!", __FUNCTION__);
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	result = inputDevice->SetDataFormat(&c_dfDIKeyboard);

	result = inputDevice->SetCooperativeLevel(handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	auto dipdw = DIPROPDWORD{};

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	result = inputDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	result = inputDevice->Acquire();

	if (result != DI_OK)
		FileLogger::GetInstance().Error("{}(): DINPUT8::Acquire failed!", __FUNCTION__);
	else
		FileLogger::GetInstance().Info("Keyboard has been initialized successfully");
}

void Keyboard::Register(IController *controller)
{
	Keyboard::controller = controller;
}

KeyboardState Keyboard::GetState()
{
	unsigned char keyStates[KEYSTATE_BUFFER_SIZE]; // DirectInput keyboard state buffer 

	// Collect all key states first
	auto result = inputDevice->GetDeviceState(sizeof(keyStates), keyStates);

	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			result = inputDevice->Acquire();

			if (result == DI_OK)
				FileLogger::GetInstance().Info("Keyboard re-acquired!");

			return KeyboardState{ nullptr };
		}
		else
		{
			FileLogger::GetInstance().Error("{}(): DINPUT::GetDeviceState failed: {}", __FUNCTION__, result);
			return KeyboardState{ nullptr };
		}
	}

	return KeyboardState{ keyStates };
}

void Keyboard::Update()
{
	if (controller == nullptr)
		return;

	controller->OnKeyStateChanged(GetState());
	HandleEvents();
}

void Keyboard::HandleEvents()
{
	// Collect all buffered events
	DeviceInputData keyEvents[KEYBOARD_BUFFER_SIZE]; // Buffered keyboard data
	auto dwElements = DWORD{ KEYBOARD_BUFFER_SIZE };
	auto result = inputDevice->GetDeviceData(sizeof(DeviceInputData), keyEvents, &dwElements, 0);

	if (FAILED(result))
	{
		// FileLogger::GetInstance().Error("DINPUT::GetDeviceData failed. Error: " + std::to_string(hr));
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		auto keyCode = keyEvents[i].dwOfs;
		auto KeyState = keyEvents[i].dwData;

		if ((KeyState & 0x80) > 0)
		{
			controller->OnKeyDown(keyCode);
		}
		else
		{
			controller->OnKeyUp(keyCode);
		}
	}
}

void Keyboard::Release()
{
	if (inputDevice != nullptr)
	{
		inputDevice->Unacquire();
		inputDevice->Release();
		inputDevice = nullptr;
	}
}