#include "AbstractScene.h"
#include "SceneManager.h"

using namespace Castlevania;

AbstractScene::AbstractScene(SceneManager &sceneManager) : sceneManager{ sceneManager }
{
}

AbstractScene::~AbstractScene()
{
}