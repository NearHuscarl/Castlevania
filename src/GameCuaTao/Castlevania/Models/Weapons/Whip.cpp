#include "Direct2DGame/MathHelper.h"
#include "Whip.h"
#include "WhipSettings.h"
#include "WhipFlashingRenderingSystem.h"

using namespace Castlevania;

const auto HITPOINTS = std::map<int, int>
{
	{ 1, 1 },
	{ 2, 2 },
	{ 3, 2 },
};

Whip::Whip(GameObject &owner) :
	GameObject{ EntityType::Whip },
	owner{ owner }
{
	level = 1;
}

int Whip::GetLevel()
{
	return level;
}

int Whip::GetAttack()
{
	return HITPOINTS.at(level);
}

GameObject &Whip::GetOwner()
{
	return owner;
}

void Whip::SetFacing(Facing facing)
{
	GameObject::SetFacing(facing);
	SendMessageToSystems(WHIP_FACING_CHANGED);
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
