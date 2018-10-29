#include "Fonts.h"

using namespace Castlevania;

SpriteFont Fonts::Main = nullptr;

void Fonts::LoadContent(ContentManager &content)
{
	Main = *content.Load<SpriteFont>("Fonts/prstartk");
}
