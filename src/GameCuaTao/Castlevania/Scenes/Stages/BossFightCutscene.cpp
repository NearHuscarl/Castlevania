#include "BossFightCutscene.h"
#include "Stage.h"
#include "StageEvent.h"

using namespace Castlevania;

constexpr auto BOSS_WAKE_UP_TIME = 2000.0f; // in milliseconds

BossFightCutscene::BossFightCutscene(Stage &stage, ObjectCollection &objectCollection, ObjectFactory &objectFactory)
	: Cutscene{ stage }
{
	for (auto &entity : objectCollection.entities)
	{
		if (entity->GetId() == ObjectId::GiantBat)
		{
			auto enemy = dynamic_cast<GiantBat*>(entity.get());
			
			boss = enemy;
			stage.GetHud()->Register(enemy->GetHealthRef());
			break;
		}
	}

	auto camera = stage.GetCamera();
	
	camera->Lock();

	auto cameraRect = camera->GetBounds();
	auto boundWidth = 16.0f; // abitrary number larger than 0
	auto leftBound = RectF{
		cameraRect.left - boundWidth,
		cameraRect.top,
		boundWidth,
		cameraRect.Height() };
	auto wall = objectFactory.CreateBoundary(leftBound);

	objectCollection.boundaries.push_back(std::move(wall));
	bossWakeupTimer.Start();
}

void BossFightCutscene::Update(GameTime gameTime)
{
	stage.UpdateGameplay(gameTime);
	
	if (bossWakeupTimer.ElapsedMilliseconds() >= BOSS_WAKE_UP_TIME)
	{
		auto moveArea = (Rect)stage.GetCamera()->GetBounds();
		
		moveArea.top += stage.GetHud()->GetHeight();
		boss->SetMoveArea(moveArea);
		boss->SetActive();
	
		stage.OnNotify(Subject::Empty(), BOSS_FIGHT_STARTED);
		isComplete = true;
	}
}
