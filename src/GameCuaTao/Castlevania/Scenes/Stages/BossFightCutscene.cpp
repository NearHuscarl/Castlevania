#include "BossFightCutscene.h"
#include "Stage.h"
#include "StageEvent.h"

using namespace Castlevania;

constexpr auto BOSS_WAKE_UP_TIME = 2000.0f; // in milliseconds

BossFightCutscene::BossFightCutscene(Stage &stage, CollisionGrid &grid, ObjectFactory &objectFactory)
	: Cutscene{ stage }
{
	auto camera = stage.GetCamera();
	auto cameraBound = camera->GetBounds();

	camera->Lock();

	grid.GetCellsFromBoundingBox(cameraBound, [&](CollisionCell &cell, int col, int row)
	{
		auto &entities = cell.GetEntites();

		for (auto &entity : entities)
		{
			if (entity->GetId() == ObjectId::GiantBat)
			{
				auto enemy = dynamic_cast<GiantBat*>(entity.get());

				boss = enemy;
				stage.GetHud()->Register(enemy->GetHealthRef());
				break; // TODO: should stop iterate all other remaining cells
			}
		}
	});

	auto boundWidth = 16.0f; // abitrary number larger than 0
	auto leftBound = RectF{
		cameraBound.left - boundWidth,
		cameraBound.top,
		boundWidth,
		cameraBound.Height() };
	auto wall = objectFactory.CreateBoundary(leftBound);

	grid.Add(std::move(wall), CollisionObjectType::Static);
	bossWakeupTimer.Start();
}

void BossFightCutscene::Update(UpdateData &updateData)
{
	stage.UpdateGameplay(updateData);
	
	if (bossWakeupTimer.ElapsedMilliseconds() >= BOSS_WAKE_UP_TIME)
	{
		auto moveArea = (Rect)stage.GetCamera()->GetBounds();
		
		moveArea.top += stage.GetHud()->GetHeight();
		boss->SetMoveArea(moveArea);
		boss->SetActive();
	
		stage.OnNotify(Subject::Empty(), CUTSCENE_ENDED);
		isComplete = true;
	}
}
