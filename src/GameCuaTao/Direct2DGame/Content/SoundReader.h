#pragma once

#include "Library/directx/DSUtil.h"
#include "AbstractReader.h"

using Sound = CSound;
using SoundManager = CSoundManager;

class SoundReader : public AbstractReader<Sound>
{
public:
	std::shared_ptr<Sound> Read(std::string filePath, ContentManager &contentManager) override;

private:
	std::unique_ptr<SoundManager> soundManager = nullptr;
	void InitDirectSound(HWND hWnd);
};