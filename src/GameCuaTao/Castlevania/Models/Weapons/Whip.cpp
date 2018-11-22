#include "Direct2DGame/MathHelper.h"
#include "Whip.h"
#include "WhipSettings.h"
#include "WhipFlashingRenderingSystem.h"

using namespace Castlevania;

const auto HITPOINTS = std::map<int, int> // TODO: do we need hitpoint?
{
	{ 1, 100 },
	{ 2, 200 },
	{ 3, 300 },
};

Whip::Whip(GameObject &owner) :
	GameObject(EntityType::Whip),
	owner{ owner }
{
	level = 1;
}

int Whip::GetLevel()
{
	return level;
}

GameObject &Whip::GetOwner()
{
	return owner;
}

void Whip::LoadContent(ContentManager &content)
{
	GameObject::LoadContent(content);
	Withdraw();
}

void Whip::Unleash()
{
	body.Enabled(true);
	SendMessageToSystems(WHIP_ENABLED_CHANGED);
}

void Whip::Withdraw()
{
	body.Enabled(false);
	SendMessageToSystems(WHIP_ENABLED_CHANGED);
}

void Whip::Upgrade()
{
	level = MathHelper::Min(++level, WHIP_MAX_LEVEL);
}
