#include "Whip.h"

using namespace Castlevania;

const auto HITPOINTS = std::map<int, int> // TODO: do we need hitpoint?
{
	{ 1, 100 },
	{ 2, 200 },
	{ 3, 300 },
};

Whip::Whip(GameObject &owner) : owner{ owner }
{
	level = 1;
}

void Whip::SetFacing(Facing facing)
{
	this->facing = facing;
}

void Whip::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>("Items/Whip.xml");
	sprite = std::make_unique<AnimatedSprite>(animationFactory);
	Withdraw();
}

void Whip::Draw(SpriteExtensions &spriteBatch)
{
	if (isActive)
	{
		if (facing == Facing::Left)
			sprite->SetEffect(SpriteEffects::FlipHorizontally);
		else
			sprite->SetEffect(SpriteEffects::None);

		// Update the sprite first before getting position so GetPositionRelativeToPlayer()
		// can access to the latest frame index
		sprite->Update();
		position = GetPositionRelativeToPlayer(owner);

		//spriteBatch.Draw(GetBoundingBox(), Color::Pink()); // TODO: remove debugging code
		spriteBatch.Draw(*sprite, position);
	}
}

void Whip::Unleash()
{
	isActive = true;
	sprite->Play("Whip_level_0" + std::to_string(level));
}

void Whip::Withdraw()
{
	isActive = false;
	sprite->GetCurrentAnimation().Reset();
}

Vector2 Whip::GetPositionRelativeToPlayer(GameObject &player)
{
	auto currentFrameIndex = sprite->GetCurrentAnimation().GetCurrentFrameIndex();
	auto playerBbox = player.GetBoundingBox();
	auto whipBbox = this->GetBoundingBox();

	if (facing == Facing::Right)
	{
		switch (currentFrameIndex)
		{
			case 0:
				return Vector2{ (float)playerBbox.left - whipBbox.Width() + 1, (float)playerBbox.top + 14 };
			case 1:
				return Vector2{ (float)playerBbox.left - whipBbox.Width(), (float)playerBbox.top + 9 };
			case 2:
				return Vector2{ (float)playerBbox.right - 3, (float)playerBbox.top + 10 };
			default:
				return Vector2::Zero();
		}
	}
	else // Facing::Left
	{
		switch (currentFrameIndex)
		{
			case 0:
				return Vector2{ (float)playerBbox.right - 1, (float)playerBbox.top + 14 };
			case 1:
				return Vector2{ (float)playerBbox.right, (float)playerBbox.top + 9 };
			case 2:
				return Vector2{ (float)playerBbox.left - whipBbox.Width() + 3, (float)playerBbox.top + 10 };
			default:
				return Vector2::Zero();
		}
	}
}
