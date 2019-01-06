#pragma once

#include "Direct2DGame/Extensions/Sprites/IDrawable.h"
#include "StageObject.h"
#include "../../Models/UpdateData.h"
#include "../../Models/Factories/ObjectFactory.h"
#include "../../Utilities/CollisionGrid.h"

namespace Castlevania
{
	class Stage;

	class Cutscene : public IDrawable
	{
	public:
		Cutscene(Stage &stage);

		bool IsComplete();

		virtual void Update(UpdateData &updateData) = 0;
		virtual void Draw(SpriteExtensions &spriteBatch) override;

	protected:
		Stage &stage;
		bool isComplete;
	};
}