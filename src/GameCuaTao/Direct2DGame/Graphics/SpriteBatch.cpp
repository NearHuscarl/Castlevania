#include "SpriteBatch.h"

SpriteBatch::SpriteBatch(GraphicsDevice &graphicsDevice)
{
	spriteHandler = graphicsDevice.GetSpriteHandler();
}

ISpriteHandler_ SpriteBatch::GetSpriteHandler()
{
	return spriteHandler;
}

void SpriteBatch::Draw(Texture &texture, Vector position, BoundingBox *rectanglePtr, Color color, SpriteEffects effects)
{
	auto rectangle = BoundingBox{};
	if (rectanglePtr == nullptr) // if null, draws full texture
		rectangle = BoundingBox(0, 0, texture.Width(), texture.Height());
	else
		rectangle = *rectanglePtr;

	auto oldMatrix = D3DXMATRIX{};
	spriteHandler->GetTransform(&oldMatrix);

	auto rotate = D3DXVECTOR2{};
	if (effects == FlipHorizontally)
		rotate = D3DXVECTOR2(-1, 1);
	else if (effects == FlipVertically)
		rotate = D3DXVECTOR2(1, -1);
	else // None
		rotate = D3DXVECTOR2(1, 1);

	auto center = D3DXVECTOR2(position.x + rectangle.Width() / 2, position.y + rectangle.Height() / 2);

	auto newMatrix = D3DXMATRIX{};
	D3DXMatrixTransformation2D(&newMatrix, &center, 0.0f, &rotate, nullptr, 0.0f, nullptr);
	auto finalMatrix = oldMatrix * newMatrix;

	spriteHandler->SetTransform(&finalMatrix);
	spriteHandler->Draw(texture.Get(), &rectangle, nullptr, &position, color.Get());
	spriteHandler->SetTransform(&oldMatrix);
}

void SpriteBatch::DrawString(SpriteFont &spriteFont, std::string text, Vector position, Color color)
{
	auto font = spriteFont.Get();
	if (font == nullptr)
		return;

	auto x = (int)position.x;
	auto y = (int)position.y;

	auto boundingBox = BoundingBox(x, y, 2000, 2000); // TODO: remove const with window width and height

	font->DrawTextA(spriteHandler, text.c_str(), -1, &boundingBox, DT_LEFT, color.Get());
}
