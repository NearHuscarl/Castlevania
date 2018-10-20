#include "SoundReader.h"
#include "ContentManager.h"
#include "LoadContentException.h"
#include "../Utilities/WinHelper.h"
#include "../GameWindow.h"

void SoundReader::InitDirectSound(HWND hWnd)
{
	// Initialize DirectSound
	soundManager = std::make_unique<SoundManager>();

	auto result = soundManager->Initialize(hWnd, DSSCL_PRIORITY);

	if (result != DS_OK)
	{
		throw LoadContentException("Cannot initialize CSoundManager");
	}

	result = soundManager->SetPrimaryBufferFormat(2, 22050, 16);

	if (result != DS_OK)
	{
		throw LoadContentException("Cannot set primary buffer format for CSoundManager");
	}
}

std::shared_ptr<Sound> SoundReader::Read(std::string filePathStr, ContentManager &contentManager)
{
	if (soundManager == nullptr)
	{
		auto handle = contentManager.GetServiceProvider().Get<GameWindow>()->GetHandle();
		InitDirectSound(handle);
	}

	CSound *wave = nullptr;

	// attempt to load the wave file
	char s[255];
	sprintf_s(s, "%s", filePathStr.c_str());

	auto filePath = WinHelper::s2ws(filePathStr);
	auto result = soundManager->Create(&wave, (LPTSTR)filePath.c_str());
	
	if (result != DS_OK)
	{
		throw LoadContentException("CSoundManager::Create() failed: " + filePathStr);
	}

	return std::shared_ptr<Sound>(wave);
}