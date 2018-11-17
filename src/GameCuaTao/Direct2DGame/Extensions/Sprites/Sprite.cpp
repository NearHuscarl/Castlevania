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
	auto offsetX = spriteBoundary.X() - spriteFrame.X();
	
	if (effect == SpriteEffects::None)
	{
		rect.left = position.x + offsetX;
		rect.right = rect.left + spriteBoundary.Width();
	}
	else if (effect == SpriteEffects::FlipHorizontally)
	{
		rect.right = position.x + spriteFrame.Width() - offsetX;
		rect.left = rect.right - spriteBoundary.Width();
	}

	rect.top = position.y + (spriteBoundary.Y() - spriteFrame.Y());
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
