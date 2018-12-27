#pragma once

#include "Container.h"

namespace Castlevania
{
	class BreakableWall : public GameObject
	{
	public:
		BreakableWall();

		void SetTopBlock(std::unique_ptr<Container> block);
		void SetBottomBlock(std::unique_ptr<Container> block);

		void SetPosition(Vector2 position) override;
		RectF GetFrameRect() override;
		RectF GetBoundingBox() override;

		void Attach(CollisionGrid *grid) override;

		void LoadContent(ContentManager &content) override;
		void Update(UpdateData &updateData) override;
		void Draw(SpriteExtensions &spriteBatch) override;

		void TakeDamage();

	private:
		std::unique_ptr<Container> topBlock;
		std::unique_ptr<Container> bottomBlock;
	};
}