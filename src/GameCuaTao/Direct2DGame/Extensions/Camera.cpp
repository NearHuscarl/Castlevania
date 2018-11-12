#include "Camera.h"
#include "Direct2DGame/MathHelper.h"

Camera::Camera(GraphicsDevice &graphicsDevice) : graphicsDevice{ graphicsDevice }
{
	moveArea = Rect::Empty();
}

void Camera::SetMoveArea(int x, int y, int width, int height)
{
	SetMoveArea(Rect(x, y, width, height));
}

void Camera::SetMoveArea(Rect moveArea)
{
	this->moveArea = moveArea;
}

Rect Camera::GetBounds()
{
	return viewport.Bounds();
}

void Camera::Move(Vector2 position)
{
	viewport.x += position.x;
	viewport.y += position.y;

	ClampMove();
}

void Camera::LookAt(Vector2 position, Scrolling scrolling)
{
	if (scrolling == Scrolling::Center || scrolling == Scrolling::Horizontally)
		viewport.x = position.x - viewport.width / 2;

	if (scrolling == Scrolling::Center || scrolling == Scrolling::Vertically)
		viewport.y = position.y - viewport.height / 2;

	ClampMove();
}

Vector2 Camera::ScreenToWorld(Vector2 screenPosition)
{
	return viewport.Unproject(screenPosition);
}

Vector2 Camera::WorldToScreen(Vector2 worldPosition)
{
	return viewport.Project(worldPosition);
}

void Camera::ClampMove()
{
	if (moveArea == Rect::Empty())
		return;

	viewport.x = MathHelper::Min(viewport.x, (float)moveArea.Width() - viewport.width);
	viewport.y = MathHelper::Min(viewport.y, (float)moveArea.Height() - viewport.height);
	viewport.x = MathHelper::Max(viewport.x, (float)moveArea.X());
	viewport.y = MathHelper::Max(viewport.y, (float)moveArea.Y());
}
