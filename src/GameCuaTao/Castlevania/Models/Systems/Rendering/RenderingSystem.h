#pragma once

#include "Direct2DGame/Extensions/Sprites/Sprite.h"
#include "IRenderingSystem.h"

namespace Castlevania
{
	// Base rendering system shipped with a bounding box drawer
	class RenderingSystem : public IRenderingSystem
	{
	public:
		RenderingSystem();

		virtual Sprite &GetSprite() override = 0;
		virtual GameObject &GetParent();
		void DrawBoundingBox(bool value);

		virtual void Receive(int message) override;

		virtual void LoadContent(ContentManager &content) override;
		virtual void Update(GameTime gameTime) override;
		virtual void Draw(SpriteExtensions &spriteBatch) override;
		void DrawBoundingBox(SpriteExtensions &spriteBatch, RectF boundingBox, Color color);

	protected:
		std::shared_ptr<Texture> bboxTexture;

		virtual void OnMoveStateChanged();
		virtual void OnStateChanged();

	private:
		bool drawBoundingBox;

		Color GetBoundingBoxColor();
	};
}
