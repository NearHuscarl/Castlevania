#include "SpriteFont.h"
#include "../Base/Rect.h"

SpriteFont::SpriteFont(IFont_ font) noexcept
{
	this->font = font;
}

SpriteFont::SpriteFont(SpriteFont &&rhs) noexcept : font{ rhs.font }
{
	rhs.font = nullptr;
}

SpriteFont &SpriteFont::operator=(SpriteFont &&rhs) noexcept
{
	font = rhs.font;
	rhs.font = nullptr;
	return *this;
}

IFont_ SpriteFont::Get() const noexcept
{
	return font;
}

Vector2 SpriteFont::MessureString(const std::string &text)
{
	if (font == nullptr)
	{
		return Vector2::Zero();
	}

	auto rect = Rect{};
	auto str = text.c_str();

	// calculate required rect
	font->DrawTextA(nullptr, str, strlen(str), &rect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));

	auto width = (float)(rect.right - rect.left);
	auto height = (float)(rect.bottom - rect.top);

	return Vector2{ width, height };
}

SpriteFont::~SpriteFont() noexcept
{
	if (font != nullptr)
	{
		font->Release();
		font = nullptr;
	}
}
