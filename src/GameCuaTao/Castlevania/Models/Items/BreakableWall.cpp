#include "BreakableWall.h"
#include "../Settings.h"

using namespace Castlevania;

BreakableWall::BreakableWall() : GameObject{ ObjectId::BreakableWall }
{
}

void BreakableWall::SetTopBlock(std::unique_ptr<Container> block)
{
	topBlock = std::move(block);
}

void BreakableWall::SetBottomBlock(std::unique_ptr<Container> block)
{
	bottomBlock = std::move(block);
}

void BreakableWall::SetPosition(Vector2 position)
{
	topBlock->SetPosition(position);

	auto bottomPosition = Vector2{
		position.x,
		position.y + topBlock->GetBoundingBox().Height() };

	bottomBlock->SetPosition(bottomPosition);
}

RectF BreakableWall::GetFrameRect()
{
	return RectF::Merge(topBlock->GetFrameRect(), bottomBlock->GetFrameRect());
}

RectF BreakableWall::GetBoundingBox()
{
	if (bottomBlock->GetState() != ObjectState::NORMAL && topBlock->GetState() != ObjectState::NORMAL)
		return RectF::Empty();
	
	return RectF::Merge(topBlock->GetBoundingBox(), bottomBlock->GetBoundingBox());
}

void BreakableWall::Attach(CollisionGrid *grid)
{
	bottomBlock->Attach(grid);
	topBlock->Attach(grid);
}

void BreakableWall::LoadContent(ContentManager &content)
{
	bottomBlock->LoadContent(content);
	topBlock->LoadContent(content);
}

void BreakableWall::Update(UpdateData &updateData)
{
	bottomBlock->Update(updateData);
	topBlock->Update(updateData);

	if (bottomBlock->GetState() == ObjectState::DEAD && topBlock->GetState() == ObjectState::DEAD)
		Destroy();
}

void BreakableWall::Draw(SpriteExtensions &spriteBatch)
{
	bottomBlock->Draw(spriteBatch);
	topBlock->Draw(spriteBatch);
}

void BreakableWall::TakeDamage()
{
	// Always destroy bottom block first (dont apply weapon collision result to individual blocks)
	if (topBlock->GetState() == ObjectState::NORMAL && bottomBlock->GetState() != ObjectState::NORMAL)
		topBlock->OnBeingHit();

	if (bottomBlock->GetState() == ObjectState::NORMAL)
		bottomBlock->OnBeingHit();
}
