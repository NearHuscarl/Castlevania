#include "SpriteBatch.h"
#include "../Base/Vector3.h"

SpriteBatch::SpriteBatch(GraphicsDevice &graphicsDevice)
{
	spriteHandler = graphicsDevice.GetSpriteHandler();
}

ISpriteHandler_ SpriteBatch::GetSpriteHandler()
{
	return spriteHandler;
}

void SpriteBatch::Draw(Texture &texture, Vector2 position, Rect *rectPtr, Color color, SpriteEffects effects)
{
	auto rect = Rect{};
	if (rectPtr == nullptr) // if null, draws full texture
		rect = Rect(0, 0, texture.Width(), texture.Height());
	else
		rect = *rectPtr;

	auto scale = Vector2{};
	if (effects == FlipHorizontally)
		scale = Vector2(-1, 1);
	else if (effects == FlipVertically)
		scale = Vector2(1, -1);
	else // None
		scale = Vector2(1, 1);

	auto center = Vector2(position.x + rect.Width() / 2, position.y + rect.Height() / 2);

	auto oldMatrix = Matrix{};
	auto newMatrix = Matrix{};
	
	spriteHandler->GetTransform(&oldMatrix);
	D3DXMatrixTransformation2D(
		&newMatrix, // the result matrix
		&center,    // scaling center vector
		0.0f,       // scaling rotation value
		&scale,     // scaling vector
		nullptr,    // rotating center/pivot vector
		0.0f,       // rotating angle
		nullptr     // translating vector
	);

	spriteHandler->SetTransform(&newMatrix);
	spriteHandler->Draw(texture.Get(), &rect, nullptr, &Vector3(position), color.Get());
	spriteHandler->SetTransform(&oldMatrix);
}

void SpriteBatch::DrawString(SpriteFont &spriteFont, std::string text, Vector2 position, Color color)
{
	auto font = spriteFont.Get();
	if (font == nullptr)
		return;

	auto textSize = spriteFont.MessureString(text);
	auto rect = Rect{};

	auto x = (int)position.x;
	auto y = (int)position.y;
	auto textWidth = (int)textSize.x;
	auto textHeight = (int)textSize.y;

	rect.left = x;
	rect.top = y;
	rect.right = x + textWidth;
	rect.bottom = y + textHeight;

	font->DrawTextA(spriteHandler, text.c_str(), -1, &rect, DT_LEFT, color.Get());
}
