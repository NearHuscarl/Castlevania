#pragma once

enum class DeviceDriverType
{
	// Hardware device been used for rendering. Maximum speed and performance.
	Hardware,

	// Emulates the hardware device on CPU. Slowly, only for testing.
	Reference,

	// Useful when DriverType.Hardware acceleration does not work.
	Software,
};