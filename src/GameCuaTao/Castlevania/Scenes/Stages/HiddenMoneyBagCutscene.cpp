#include "HiddenMoneyBagCutscene.h"
#include "Stage.h"
#include "StageEvent.h"
#include "../../Utilities/AudioManager.h"

using namespace Castlevania;

HiddenMoneyBagCutscene::HiddenMoneyBagCutscene(
	Stage &stage,
	StageObject &stageObject,
	CollisionGrid &grid,
	ObjectFactory &objectFactory)
	:
	Cutscene{ stage }
{
	auto spawnPoint = stageObject.locations.at("MoneyBag").position;
	auto moneyBag = objectFactory.CreateFlashingMoneyBag(spawnPoint);

	hiddenMoneyBag = moneyBag.get();
	hiddenMoneyBag->Detach<IMovementSystem>();

	moneyBagPosition = spawnPoint;
	emergeEndPoint = Vector2{ spawnPoint.x, spawnPoint.y - moneyBag->GetFrameRect().Height() };

	grid.Add(std::move(moneyBag), CollisionObjectType::Entity);
	AudioManager::Play(SE_HIDDEN_MONEY_BAG_FOUND);
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
