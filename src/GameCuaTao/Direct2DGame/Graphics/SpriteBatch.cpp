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

void SpriteBatch::Draw(Texture &texture, Vector2 position, BoundingBox *rectanglePtr, Color color, SpriteEffects effects)
{
	auto rectangle = BoundingBox{};
	if (rectanglePtr == nullptr) // if null, draws full texture
		rectangle = BoundingBox(0, 0, texture.Width(), texture.Height());
	else
		rectangle = *rectanglePtr;

	auto scale = Vector2{};
	if (effects == FlipHorizontally)
		scale = Vector2(-1, 1);
	else if (effects == FlipVertically)
		scale = Vector2(1, -1);
	else // None
		scale = Vector2(1, 1);

	auto center = Vector2(position.x + rectangle.Width() / 2, position.y + rectangle.Height() / 2);

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
	spriteHandler->Draw(texture.Get(), &rectangle, nullptr, &Vector3(position), color.Get());
	spriteHandler->SetTransform(&oldMatrix);
}

void SpriteBatch::DrawString(SpriteFont &spriteFont, std::string text, Vector2 position, Color color)
{
	auto font = spriteFont.Get();
	if (font == nullptr)
		return;

	auto x = (int)position.x;
	auto y = (int)position.y;

	auto boundingBox = BoundingBox(x, y, 2000, 2000); // TODO: remove const with window width and height

	font->DrawTextA(spriteHandler, text.c_str(), -1, &boundingBox, DT_LEFT, color.Get());
}
