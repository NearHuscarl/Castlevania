#include "CrossCutscene.h"
#include "Stage.h"
#include "StageEvent.h"
#include "../../Utilities/MapSettings.h"

using namespace Castlevania;

constexpr auto CROSS_TIME = 650; // in milliseconds

CrossCutscene::CrossCutscene(Stage &stage, ContentManager &content, CollisionGrid &grid) :
	Cutscene{ stage },
	grid{ grid }
{
	auto backgroundTexture = content.Load<Texture>("Backgrounds/BoundingBox.png");
	background = std::make_unique<Sprite>(backgroundTexture);

	crossTimer.Start();
}

void CrossCutscene::Update(UpdateData &updateData)
{
	grid.GetCellsFromBoundingBox(stage.GetCamera()->GetBounds(), [&](CollisionCell &cell, int col, int row)
	{
		auto &entities = cell.GetEntites();

		for (auto &entity : entities)
		{
			auto enemy = dynamic_cast<Enemy*>(entity.get());

			if (enemy != nullptr)
				enemy->Die();
		}
	});

	stage.UpdateGameplay(updateData);

	if (crossTimer.ElapsedMilliseconds() >= CROSS_TIME)
	{
		stage.OnNotify(Subject::Empty(), CUTSCENE_ENDED);
		isComplete = true;
	}
}

void CrossCutscene::Draw(SpriteExtensions &spriteBatch)
{
	auto backgroundColor = background->GetColor() == MAP_BLACK_COLOR ? MAP_WHITE_COLOR : MAP_BLACK_COLOR;
	background->SetColor(backgroundColor);

	spriteBatch.Draw(*background, Vector2::Zero(), false);
	Cutscene::Draw(spriteBatch);
}
