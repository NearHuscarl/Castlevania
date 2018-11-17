#include "SpriteExtensions.h"
#include "Direct2DGame/MathHelper.h"

SpriteExtensions::SpriteExtensions(GraphicsDevice &graphicsDevice) : SpriteBatch(graphicsDevice)
{
	auto renderDevice = graphicsDevice.GetRenderDevice();
	auto viewport = graphicsDevice.GetViewport();

	renderDevice->CreateOffscreenPlainSurface(
		viewport.width,  // Width of the surface
		viewport.height, // Height of the surface
		D3DFMT_X8R8G8B8, // Surface format
		D3DPOOL_DEFAULT, // Memory pool to use
		&plainSurface,   // Pointer to ther surface
		nullptr);        // Reserved (always nullptr)
}

void SpriteExtensions::Draw(Sprite sprite, Transform transform)
{
	Draw(sprite, transform.position, transform.rotation, transform.scale);
}

void SpriteExtensions::Draw(Sprite sprite, Vector2 position, float rotation, Vector2 scale)
{
	if (sprite.IsVisible())
	{
		auto &texture = sprite.GetTextureRegion().GetTexture();
		auto spriteFrame = sprite.GetTextureRegion().GetFrameRectangle();
		auto color = sprite.GetColor() * sprite.GetAlpha();
		auto effect = sprite.GetEffect();

		Draw(texture, position, &spriteFrame, color, rotation, scale, effect);
	}
}

void SpriteExtensions::Draw(RectF rect, Color color)
{
	End(); // Force drawing all sprites so the surface will be drawn on the next Begin() call
	Begin(D3DXSPRITE_ALPHABLEND);

	auto renderDevice = graphicsDevice.GetRenderDevice();
	auto surface = graphicsDevice.GetSurface();
	auto viewport = graphicsDevice.GetViewport();
	auto camPosition = viewport.Project(rect.X(), rect.Y());
	auto destRect = RectF{ camPosition.x, camPosition.y, rect.Width(), rect.Height() };

	// Clamp width for ground rect because surface will not be drawn on screen when its width
	// and height excess screen size
	destRect.left = MathHelper::Max(destRect.left, viewport.x + 2);
	destRect.right = MathHelper::Min(destRect.right, viewport.x + viewport.width - 2);

	renderDevice->ColorFill(plainSurface, nullptr, color.Get());
	renderDevice->StretchRect(plainSurface, nullptr, surface, &(Rect)destRect, D3DTEXF_NONE);
}
