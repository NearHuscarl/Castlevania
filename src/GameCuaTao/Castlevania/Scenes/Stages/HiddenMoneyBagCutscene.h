#pragma once

#include "Cutscene.h"
#include "../../Models/Items/Powerup.h"

namespace Castlevania
{
	class HiddenMoneyBagCutscene : public Cutscene
	{
	public:
		HiddenMoneyBagCutscene(
			Stage &stage,
			StageObject &stageObject,
			CollisionGrid &grid,
			ObjectFactory &objectFactory);

		void Update(UpdateData &updateData) override;

	private:
		Vector2 moneyBagPosition;
		Vector2 emergeEndPoint;
		Powerup *hiddenMoneyBag;
	};
}