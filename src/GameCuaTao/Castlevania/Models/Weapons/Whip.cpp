#include "Direct2DGame/MathHelper.h"
#include "Whip.h"
#include "../Settings.h"
#include "WhipFlashingRenderingSystem.h"
#include "../../Utilities/AudioManager.h"

using namespace Castlevania;

const auto HITPOINTS = std::map<int, int>
{
	{ 1, 1 },
	{ 2, 2 },
	{ 3, 2 },
};

Whip::Whip() : GameObject{ ObjectId::Whip }
{
	level = 1;
}

int Whip::GetLevel()
{
	return level;
}

void Whip::SetLevel(int level)
{
	this->level = MathHelper::Clamp(level, 1, WHIP_MAX_LEVEL);
}

int Whip::GetAttack()
{
	return HITPOINTS.at(level);
}

void Whip::SetAttack(int attack)
{
}

GameObject *Whip::GetOwner()
{
	return owner;
}

void Whip::SetOwner(GameObject *owner)
{
	this->owner = owner;
}

void Whip::SetFacing(Facing facing)
{
	GameObject::SetFacing(facing);
	SendMessageToSystems(FACING_CHANGED);
}

void Whip::LoadContent(ContentManager &content)
{
	GameObject::LoadContent(content);
	Withdraw();
}

void Whip::Unleash()
{
	// Collision detection will be turn on when whip is on the attack frame
	// body.Enabled(true);
	SendMessageToSystems(WHIP_UNLEASHED);
	AudioManager::Play(SE_USING_WEAPON);
}

void Whip::Withdraw()
{
	body.Enabled(false);
	SendMessageToSystems(WEAPON_WITHDRAWN);
}

void Whip::Upgrade()
{
	level = MathHelper::Min(++level, WHIP_MAX_LEVEL);
}
