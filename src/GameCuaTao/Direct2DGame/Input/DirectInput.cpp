#include "DirectInput.h"
#include "../Utilities/FileLogger.h"

Input_ DirectInput::input = nullptr;
HWND DirectInput::handle;

void DirectInput::Initialize(HWND handle)
{
	DirectInput::handle = handle;

	auto result = DirectInput8Create(
		(HINSTANCE)GetWindowLong(handle, GWL_HINSTANCE),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&input, nullptr);

	if (result != DI_OK)
	{
		FileLogger::GetInstance().Error("{}(): DirectInput8Create failed!", __FUNCTION__);
		return;
	}
}

Input_ DirectInput::GetInput()
{
	return input;
}

HWND DirectInput::GetHandle()
{
	return handle;
}
