#include "Sprite.h"

Sprite::Sprite(std::shared_ptr<Texture> texture)
	: Sprite(TextureRegion{ texture })
{
}

Sprite::Sprite(TextureRegion textureRegion) : textureRegion{ textureRegion }
{
	alpha = 1.0f;
	color = Color::White();
	isVisible = true;
	effect = SpriteEffects::None;
}

void Sprite::SetTextureRegion(TextureRegion textureRegion)
{
	this->textureRegion = textureRegion;
}

TextureRegion Sprite::GetTextureRegion()
{
	return textureRegion;
}

RectF Sprite::GetFrameRectangle(Vector2 position)
{
	auto spriteFrame = textureRegion.GetFrameRectangle();
	auto rect = RectF{};

	rect.left = position.x;
	rect.top = position.y;
	rect.right = rect.left + spriteFrame.Width();
	rect.bottom = rect.top + spriteFrame.Height();

	return rect;
}

RectF Sprite::GetBoundingRectangle(Vector2 position)
{
	auto spriteFrame = textureRegion.GetFrameRectangle();
	auto spriteBoundary = textureRegion.GetBoundingRectangle();
	auto rect = RectF{};
	// spriteFrame is usually larger than the spriteBoundary so we need to take account of the offset
	auto offset_x = spriteBoundary.X() - spriteFrame.X();
	auto offset_y = spriteBoundary.Y() - spriteFrame.Y();

	if (effect == SpriteEffects::None)
	{
		rect.left = position.x + offset_x;
		rect.right = rect.left + spriteBoundary.Width();
	}
	else if (effect == SpriteEffects::FlipHorizontally)
	{
		rect.right = position.x + spriteFrame.Width() - offset_x;
		rect.left = rect.right - spriteBoundary.Width();
	}

	rect.top = position.y + offset_y;
	rect.bottom = rect.top + spriteBoundary.Height();

	return rect;
}

void Sprite::SetAlpha(float alpha)
{
	this->alpha = alpha;
}

float Sprite::GetAlpha()
{
	return alpha;
}

void Sprite::SetColor(Color color)
{
	this->color = color;
}

Color Sprite::GetColor()
{
	return color;
}

void Sprite::SetVisibility(bool isVisible)
{
	this->isVisible = isVisible;
}

bool Sprite::IsVisible()
{
	return isVisible;
}

void Sprite::SetEffect(SpriteEffects effect)
{
	this->effect = effect;
}

SpriteEffects Sprite::GetEffect()
{
	return effect;
}
