#include "SpriteBatch.h"
#include "../Base/Vector3.h"

SpriteBatch::SpriteBatch(GraphicsDevice &graphicsDevice) : graphicsDevice{ graphicsDevice }
{
	spriteHandler = graphicsDevice.GetSpriteHandler();
}

GraphicsDevice &SpriteBatch::GetGraphicsDevice()
{
	return graphicsDevice;
}

void SpriteBatch::Begin(unsigned long flag)
{
	spriteHandler->Begin(flag);
}

void SpriteBatch::End()
{
	spriteHandler->End();
}

void SpriteBatch::Draw(Texture &texture, Vector2 position, Color color)
{
	Draw(texture, position, nullptr, color, 0.0f, Vector2::One(), SpriteEffects::None);
}

void SpriteBatch::Draw(Texture &texture, Vector2 position, Rect *rectPtr, Color color, float rotation, Vector2 scale, SpriteEffects effects)
{
	auto rect = Rect{};
	if (rectPtr == nullptr) // if null, draws full texture
		rect = Rect{ 0, 0, texture.Width(), texture.Height() };
	else
		rect = *rectPtr;

	auto scaleVec = Vector2{};
	if (effects == SpriteEffects::FlipHorizontally)
		scaleVec = Vector2{ -1, 1 } * scale;
	else if (effects == SpriteEffects::FlipVertically)
		scaleVec = Vector2{ 1, -1 } * scale;
	else // SpriteEffects::None
		scaleVec = Vector2{ 1, 1 } * scale;

	position = graphicsDevice.GetViewport().Project(position);
	auto center = Vector2{ position.x + rect.Width() / 2, position.y + rect.Height() / 2 };

	auto oldMatrix = Matrix{};
	auto newMatrix = Matrix{};
	
	spriteHandler->GetTransform(&oldMatrix);
	D3DXMatrixTransformation2D(
		&newMatrix, // the result matrix
		&center,    // scaling center vector
		0.0f,       // scaling rotation value
		&scaleVec,  // scaling vector
		&center,    // rotating center/pivot vector
		rotation,   // rotating angle (radians)
		nullptr     // translating vector
	);

	spriteHandler->SetTransform(&newMatrix);
	spriteHandler->Draw(texture.Get(), &rect, nullptr, &Vector3{ position }, color.Get());
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
