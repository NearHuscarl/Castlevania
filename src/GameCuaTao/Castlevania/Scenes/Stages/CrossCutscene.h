#pragma once

#include "Direct2DGame/Utilities/Stopwatch.h"
#include "Cutscene.h"

namespace Castlevania
{
	class CrossCutscene : public Cutscene
	{
	public:
		CrossCutscene(Stage &stage, ContentManager &content, CollisionGrid &grid);

		void Update(UpdateData &updateData) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		std::unique_ptr<Sprite> background;
		Stopwatch crossTimer;
		CollisionGrid &grid;
	};
}