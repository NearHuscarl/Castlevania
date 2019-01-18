#pragma once

#include <string>
#include "../Direct3D9.h"
#include "../Base/Vector2.h"

class SpriteFont
{
public:
	SpriteFont(IFont_ font) noexcept;

	SpriteFont(SpriteFont &&rhs) noexcept;
	SpriteFont &operator=(SpriteFont &&rhs) noexcept;

	IFont_ Get() const noexcept;
	Vector2 MessureString(const std::string &text);

	~SpriteFont() noexcept;

private:
	IFont_ font;
};