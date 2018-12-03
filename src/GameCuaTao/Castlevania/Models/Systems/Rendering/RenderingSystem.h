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

		virtual void Receive(int message) override {};

		virtual void LoadContent(ContentManager &content) override;
		virtual void Update(GameTime gameTime) override;
		virtual void Draw(SpriteExtensions &spriteBatch) override;

	protected:
		std::shared_ptr<Texture> bboxTexture;

	private:
		bool drawBoundingBox;

		Color GetBoundingBoxColor();
	};
}
