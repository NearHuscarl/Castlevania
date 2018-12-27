#include "HiddenMoneyBagCutscene.h"
#include "Stage.h"
#include "StageEvent.h"

using namespace Castlevania;

HiddenMoneyBagCutscene::HiddenMoneyBagCutscene(
	Stage &stage,
	StageObject &stageObject,
	CollisionGrid &grid,
	ObjectFactory &objectFactory)
	:
	Cutscene{ stage }
{
	auto spawnPoint = stageObject.locations.at("MoneyBag");
	auto moneyBag = objectFactory.CreateFlashingMoneyBag(spawnPoint);

	hiddenMoneyBag = moneyBag.get();
	hiddenMoneyBag->SetVelocity_Y(0);

	moneyBagPosition = spawnPoint;
	emergeEndPoint = Vector2{ spawnPoint.x, spawnPoint.y - moneyBag->GetFrameRect().Height() };

	grid.Add(std::move(moneyBag), CollisionObjectType::Entity);
}

void HiddenMoneyBagCutscene::Update(UpdateData &updateData)
{
	stage.UpdateGameplay(updateData);

	moneyBagPosition.y -= 0.5f;

	if (moneyBagPosition.y < emergeEndPoint.y)
	{
		hiddenMoneyBag->Spawn();
		stage.OnNotify(Subject::Empty(), CUTSCENE_ENDED);
		isComplete = true;
	}

	hiddenMoneyBag->SetPosition(moneyBagPosition);
}
