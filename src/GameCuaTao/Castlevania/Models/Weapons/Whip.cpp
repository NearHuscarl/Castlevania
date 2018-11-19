#include "Whip.h"

using namespace Castlevania;

const auto HITPOINTS = std::map<int, int> // TODO: do we need hitpoint?
{
	{ 1, 100 },
	{ 2, 200 },
	{ 3, 300 },
};

Whip::Whip(GameObject &owner) :
	AnimatedObject(EntityType::Whip),
	owner{ owner }
{
	level = 1;
}

void Whip::SetFacing(Facing facing)
{
	this->facing = facing;
}

RectF Whip::GetBoundingBox()
{
	if (!body.Enabled())
		return RectF::Empty();

	return AnimatedObject::GetBoundingBox();
}

void Whip::LoadContent(ContentManager &content)
{
	AnimatedObject::LoadContent(content);
	Withdraw();
}

void Whip::Update(float deltaTime, ObjectCollection *objectCollection)
{
	if (body.Enabled())
	{
		AnimatedObject::Update(deltaTime, objectCollection);

		// Update the animations first before getting position so GetPositionRelativeToPlayer()
		// can access to the latest frame index
		position = GetPositionRelativeToPlayer(owner);
	}
}

void Whip::Draw(SpriteExtensions &spriteBatch)
{
	if (body.Enabled())
	{
		AnimatedObject::Draw(spriteBatch);
	}
}

void Whip::Unleash()
{
	body.Enabled(true);
	GetSprite().Play("Whip_level_0" + std::to_string(level));
}

void Whip::Withdraw()
{
	body.Enabled(false);
	GetSprite().GetCurrentAnimation().Reset();
}

Vector2 Whip::GetPositionRelativeToPlayer(GameObject &player)
{
	auto currentFrameIndex = GetSprite().GetCurrentAnimation().GetCurrentFrameIndex();
	auto playerBbox = player.GetBoundingBox();
	auto whipBbox = this->GetBoundingBox();

	if (facing == Facing::Right)
	{
		switch (currentFrameIndex)
		{
			case 0:
				return Vector2{ playerBbox.left - whipBbox.Width() + 1, playerBbox.top + 14 };
			case 1:
				return Vector2{ playerBbox.left - whipBbox.Width(), playerBbox.top + 9 };
			case 2:
				return Vector2{ playerBbox.right - 3, playerBbox.top + 10 };
			default:
				return Vector2::Zero();
		}
	}
	else // Facing::Left
	{
		switch (currentFrameIndex)
		{
			case 0:
				return Vector2{ playerBbox.right - 1, playerBbox.top + 14 };
			case 1:
				return Vector2{ playerBbox.right, playerBbox.top + 9 };
			case 2:
				return Vector2{ playerBbox.left - whipBbox.Width() + 3, playerBbox.top + 10 };
			default:
				return Vector2::Zero();
		}
	}
}
