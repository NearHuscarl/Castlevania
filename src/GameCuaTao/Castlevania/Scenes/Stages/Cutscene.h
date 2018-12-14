#pragma once

#include "Direct2DGame/IUpdateable.h"
#include "Direct2DGame/Extensions/Sprites/IDrawable.h"

namespace Castlevania
{
	class Stage;

	class Cutscene : public IUpdateable, public IDrawable
	{
	public:
		Cutscene(Stage &stage);

		bool IsComplete();

		virtual void Update(GameTime gameTime) override = 0;
		virtual void Draw(SpriteExtensions &spriteBatch) override;

	protected:
		Stage &stage;
		bool isComplete;
	};
}