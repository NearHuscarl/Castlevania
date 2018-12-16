#pragma once

#include "../Graphics/GraphicsDevice.h"

enum class Scrolling
{
	Horizontally,
	Vertically,
	Center,
};

class Camera
{
public:
	Camera(GraphicsDevice &graphicsDevice);

	void SetMoveArea(int x, int y, int width, int height);
	void SetMoveArea(Rect moveArea);
	RectF GetBounds();

	void Move(Vector2 position);
	void LookAt(Vector2 position, Scrolling scrolling = Scrolling::Center);
	void Lock();

	Vector2 ScreenToWorld(Vector2 screenPosition);
	Vector2 WorldToScreen(Vector2 worldPosition);

private:
	Rect moveArea;
	GraphicsDevice &graphicsDevice;
	Viewport &viewport = graphicsDevice.GetViewport();
	
	void ClampMove();
};