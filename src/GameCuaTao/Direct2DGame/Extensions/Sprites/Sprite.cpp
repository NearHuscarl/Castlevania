#include "Sprite.h"

Sprite::Sprite(std::shared_ptr<Texture> texture)
	: Sprite(TextureRegion(texture))
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

Rect Sprite::GetFrameRectangle(Transform transform)
{
	auto spriteFrame = textureRegion.GetFrameRectangle();
	auto position = transform.position;
	auto rect = Rect{};

	rect.left = (int)position.x;
	rect.top = (int)position.y;
	rect.right = rect.left + spriteFrame.Width();
	rect.bottom = rect.top + spriteFrame.Height();

	return rect;
}

Rect Sprite::GetBoundingRectangle(Transform transform)
{
	auto spriteFrame = textureRegion.GetFrameRectangle();
	auto spriteBoundary = textureRegion.GetBoundingRectangle();
	auto position = transform.position;
	auto rect = Rect{};

	// spriteFrame is usually larger than the spriteBoundary so we need to take account of the offset
	rect.left = (int)position.x + (spriteFrame.X() - spriteBoundary.X());
	rect.top = (int)position.y + (spriteFrame.Y() - spriteBoundary.Y());
	rect.right = rect.left + spriteBoundary.Width();
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

void Sprite::SetIsVisible(bool isVisible)
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
