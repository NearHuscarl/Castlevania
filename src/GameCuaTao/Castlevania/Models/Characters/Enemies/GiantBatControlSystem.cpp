#include "Direct2DGame/MathHelper.h"
#include "GiantBatControlSystem.h"
#include "../../UpdateData.h"
#include "../../Settings.h"

using namespace Castlevania;

GiantBatControlSystem::GiantBatControlSystem(GiantBat &parent, ObjectFactory &objectFactory) :
	parent{ parent },
	objectFactory{ objectFactory }
{
}

void GiantBatControlSystem::Update(UpdateData &updateData)
{
	switch (parent.GetGiantBatState())
	{
		case GiantBatState::IDLE:
			//parent.Hover();
			break;
	}
}
