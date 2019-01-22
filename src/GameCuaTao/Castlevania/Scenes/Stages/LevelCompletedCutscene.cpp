#include "Direct2DGame/MathHelper.h"
#include "LevelCompletedCutscene.h"
#include "Stage.h"
#include "StageEvent.h"
#include "../../Utilities/AudioManager.h"

using namespace Castlevania;

constexpr auto CRYSTAL_BALL_HOVERING_TRANSITION_TIME = 1000;
constexpr auto CONVERTING_TIME_REMAINING_TO_EXP_TRANSITION_TIME = 500;
constexpr auto CONVERTING_TIME_REMAINING_TO_EXP_SOUND_EFFECT_UPDATE_TIME = 130;
constexpr auto CONVERTING_HEART_TO_EXP_TRANSITION_TIME = 1000;
constexpr auto TIME_TO_EXP_UPDATE_TIME = 20;
constexpr auto HEART_TO_EXP_UPDATE_TIME = 130;

enum class LevelCompletedCutscene::State
{
	CRYSTAL_BALL_HOVERING,
	CRYSTAL_BALL_ON_GROUND,
	CONVERTING_TIME_REMAINING_TO_EXP,
	CONVERTING_HEART_TO_EXP,
};

LevelCompletedCutscene::LevelCompletedCutscene(
	Stage &stage,
	CollisionGrid &grid,
	ObjectFactory &objectFactory,
	Player &player,
	GameplayData &gameplayData)
	:
	Cutscene{ stage },
	player{ player },
	gameplayData{ gameplayData }
{
	auto viewport = stage.GetCamera()->GetBounds();
	auto crystalBallPosition = Vector2{
		viewport.left + viewport.Width() / 2 - 14,
		viewport.top + viewport.Height() / 2 };
	auto crystalBall = objectFactory.CreateCrystalBall(crystalBallPosition);
	
	this->crystalBall = crystalBall.get();
	this->crystalBall->EnableMovement(false);
	
	grid.Add(std::move(crystalBall), CollisionObjectType::Entity);
	transitionTimer.Start();
}

void LevelCompletedCutscene::Update(UpdateData &updateData)
{
	switch (currentState)
	{
		case State::CRYSTAL_BALL_HOVERING:
			stage.UpdateGameplay(updateData);

			if (transitionTimer.ElapsedMilliseconds() >= CRYSTAL_BALL_HOVERING_TRANSITION_TIME)
			{
				transitionTimer.Reset();
				crystalBall->EnableMovement(true);
				currentState = State::CRYSTAL_BALL_ON_GROUND;
			}
			break;

		case State::CRYSTAL_BALL_ON_GROUND:
			// check if crystalBall not point to garbage. kinda hacky but works
			if (crystalBall->GetId() == ObjectId::CrystalBall && crystalBall->GetState() != ObjectState::DEAD)
				stage.UpdateGameplay(updateData);
			else
			{
				updateData.isStopwatchActive = true;
				stage.UpdateGameplay(updateData);

				if (!transitionTimer.IsRunning())
				{
					AudioManager::Stop(M_BOSS_BATTLE);
					AudioManager::Play(SE_STAGE_CLEAR);
					transitionTimer.Start();
				}

				if (!AudioManager::IsPlaying(SE_STAGE_CLEAR) && player.GetData().health.Value() == MAX_HEALTH)
				{
					currentState = State::CONVERTING_TIME_REMAINING_TO_EXP;
					transitionTimer.Reset();
					scoreUpdateTimer.Start();
					soundEffectTimer.Start();
				}
			}

			break;

		case State::CONVERTING_TIME_REMAINING_TO_EXP:
			if (gameplayData.timeLeft.GetCounter() > 0)
			{
				if (scoreUpdateTimer.ElapsedMilliseconds() >= TIME_TO_EXP_UPDATE_TIME)
				{
					player.AddExp(20);
					auto counter = MathHelper::Max(gameplayData.timeLeft.GetCounter() - 2, 0);
					gameplayData.timeLeft.SetCounter(counter);
					scoreUpdateTimer.Restart();
				}

				if (soundEffectTimer.ElapsedMilliseconds() >= CONVERTING_TIME_REMAINING_TO_EXP_SOUND_EFFECT_UPDATE_TIME)
				{
					AudioManager::Play(SE_GETTING_TIME_BONUS);
					soundEffectTimer.Restart();
				}
			}
			else // gameplayData.timeLeft.GetCounter() == 0
			{
				if (!transitionTimer.IsRunning())
					transitionTimer.Start();
			}

			if (transitionTimer.ElapsedMilliseconds() >= CONVERTING_TIME_REMAINING_TO_EXP_TRANSITION_TIME)
			{
				currentState = State::CONVERTING_HEART_TO_EXP;
				transitionTimer.Reset();
				scoreUpdateTimer.Start();
			}
			break;

		case State::CONVERTING_HEART_TO_EXP:
			if (player.GetData().hearts > 0)
			{
				if (scoreUpdateTimer.ElapsedMilliseconds() >= HEART_TO_EXP_UPDATE_TIME)
				{
					player.AddExp(100);
					player.AddHeart(-1);
					AudioManager::Play(SE_GETTING_HEART_BONUS);
					scoreUpdateTimer.Restart();
				}
			}
			else // (player.GetData().hearts == 0)
			{
				if (!transitionTimer.IsRunning())
					transitionTimer.Start();
			}

			if (transitionTimer.ElapsedMilliseconds() >= CONVERTING_HEART_TO_EXP_TRANSITION_TIME)
				stage.OnNotify(Subject::Empty(), LEVEL_COMPLETED);
			break;
	}
}
