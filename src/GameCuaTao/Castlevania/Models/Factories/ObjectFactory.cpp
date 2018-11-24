#include "ObjectFactory.h"
#include "../EntityType.h"
#include "../RectangleObject.h"
#include "../Systems/Movement/MovementSystem.h"
#include "../Systems/Collision/CollisionSystem.h"
#include "../Systems/Collision/EntityCollisionSystem.h"
#include "../Systems/Collision/StaticCollisionSystem.h"
#include "../Systems/Collision/StandardCollisionSystem.h"
#include "../Systems/CollisionResponse/StaticResponseSystem.h"
#include "../Systems/Rendering/SpriteRenderingSystem.h"
#include "../Systems/Rendering/AnimationRenderingSystem.h"
#include "../Characters/Player/Controller.h"
#include "../Characters/Player/PlayerMovementSystem.h"
#include "../Characters/Player/PlayerCollisionSystem.h"
#include "../Characters/Player/PlayerResponseSystem.h"
#include "../Characters/Player/PlayerRenderingSystem.h"
#include "../Weapons/WhipRenderingSystem.h"
#include "../Weapons/WhipFlashingRenderingSystem.h"
#include "../Weapons/WhipResponseSystem.h"
#include "../Weapons/KnifeResponseSystem.h"

using namespace Castlevania;

constexpr auto ITEM_FALL_SPEED = 120.0f;

ObjectFactory::ObjectFactory(ContentManager &content) : content{ content }
{
	effectManager = std::make_unique<EffectFactory>(content);
}

std::unique_ptr<Bat> ObjectFactory::CreateBat(Vector2 position)
{
	auto bat = std::make_unique<Bat>();
	auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*bat, "Characters/NPCs/Bat.ani.xml");

	bat->SetPosition(position);
	bat->Attach<IRenderingSystem>(std::move(renderingSystem));
	bat->LoadContent(content);

	return bat;
}

std::unique_ptr<Player> ObjectFactory::CreatePlayer(Vector2 position)
{
	auto player = std::make_unique<Player>();

	auto controller = std::make_unique<Controller>(*player, *this);
	auto movementSystem = std::make_unique<PlayerMovementSystem>(*player);
	auto collisionSystem = std::make_unique<PlayerCollisionSystem>(*player);
	auto responseSystem = std::make_unique<PlayerResponseSystem>(*player, *this);
	auto renderingSystem = std::make_unique<PlayerRenderingSystem>(*player,
		"Characters/Players/Simon.ani.xml",
		"Characters/Players/Simon_Flashing.ani.xml");

	player->SetPosition(position);
	player->Attach<IController>(std::move(controller));
	player->Attach<IMovementSystem>(std::move(movementSystem));
	player->Attach<ICollisionSystem>(std::move(collisionSystem));
	player->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	player->Attach<IRenderingSystem>(std::move(renderingSystem));

	auto whip = CreateWhip(*player);
	
	player->SetWhip(std::move(whip));
	player->LoadContent(content);

	return player;

}

std::unique_ptr<Player> ObjectFactory::CreateSimon(Vector2 position)
{
	return std::unique_ptr<Player>();
}

std::unique_ptr<FirePit> ObjectFactory::CreateFirePit(EntityType itemType, Vector2 position)
{
	auto firePit = std::make_unique<FirePit>();

	auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*firePit, "Items/Fire_Pit.ani.xml");
	auto item = CreatePowerup(itemType);
	auto effect = effectManager->CreateFlameEffect();

	firePit->SetPosition(position);
	firePit->Attach<IRenderingSystem>(std::move(renderingSystem));
	firePit->SetSpawnedItem(std::move(item));
	firePit->SetHitEffect(std::move(effect));
	firePit->LoadContent(content);
	
	return firePit;
}

std::unique_ptr<Whip> ObjectFactory::CreateWhip(GameObject &gameObject)
{
	auto whip = std::make_unique<Whip>(gameObject);

	auto collisionSystem = std::make_unique<EntityCollisionSystem>(*whip);
	auto responseSystem = std::make_unique<WhipResponseSystem>(*whip);
	auto renderingSystem = std::make_unique<WhipRenderingSystem>(*whip, "Items/Whip.ani.xml");

	whip->Attach<ICollisionSystem>(std::move(collisionSystem));
	whip->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	whip->Attach<IRenderingSystem>(std::move(renderingSystem));

	whip->LoadContent(content);

	return whip;
}

std::unique_ptr<Whip> ObjectFactory::CreateFlashingWhip(GameObject &gameObject)
{
	auto whip = std::make_unique<Whip>(gameObject);

	auto collisionSystem = std::make_unique<EntityCollisionSystem>(*whip);
	auto responseSystem = std::make_unique<WhipResponseSystem>(*whip);
	auto renderingSystem = std::make_unique<WhipFlashingRenderingSystem>(*whip, "Items/Whip.ani.xml");

	whip->Attach<ICollisionSystem>(std::move(collisionSystem));
	whip->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	whip->Attach<IRenderingSystem>(std::move(renderingSystem));

	whip->LoadContent(content);

	return whip;
}

std::unique_ptr<RangedWeapon> ObjectFactory::CreateKnife(Vector2 position)
{
	auto knife = std::make_unique<RangedWeapon>(EntityType::Knife);

	auto movementSystem = std::make_unique<MovementSystem>(*knife);
	auto collisionSystem = std::make_unique<EntityCollisionSystem>(*knife);
	auto responseSystem = std::make_unique<KnifeResponseSystem>(*knife);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*knife, "Items/Knife.png");

	knife->SetPosition(position);
	knife->Attach<IMovementSystem>(std::move(movementSystem));
	knife->Attach<ICollisionSystem>(std::move(collisionSystem));
	knife->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	knife->Attach<IRenderingSystem>(std::move(renderingSystem));

	knife->LoadContent(content);

	return knife;
}

std::unique_ptr<Powerup> ObjectFactory::CreatePowerup(EntityType type, Vector2 position)
{
	switch (type)
	{
		case EntityType::Heart:
			return CreateHeart(position);

		case EntityType::WhipPowerup:
			return CreateWhipPowerup(position);

		case EntityType::KnifeItem:
			return CreateKnifeItem(position);

		default:
			throw std::invalid_argument("Invalid powerup type");
	}
}

std::unique_ptr<Powerup> ObjectFactory::CreateKnifeItem(Vector2 position)
{
	auto knifeItem = std::make_unique<Powerup>(EntityType::KnifeItem);

	auto movementSystem = std::make_unique<MovementSystem>(*knifeItem);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*knifeItem);
	auto responseSystem = std::make_unique<StaticResponseSystem>(*knifeItem);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*knifeItem, "Items/Knife.png");

	knifeItem->SetPosition(position);
	knifeItem->Attach<IMovementSystem>(std::move(movementSystem));
	knifeItem->Attach<ICollisionSystem>(std::move(collisionSystem));
	knifeItem->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	knifeItem->Attach<IRenderingSystem>(std::move(renderingSystem));

	knifeItem->LoadContent(content);
	knifeItem->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return knifeItem;
}

std::unique_ptr<Powerup> ObjectFactory::CreateHeart(Vector2 position)
{
	auto heart = std::make_unique<Powerup>(EntityType::Heart);

	auto movementSystem = std::make_unique<MovementSystem>(*heart);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*heart);
	auto responseSystem = std::make_unique<StaticResponseSystem>(*heart);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*heart, "Items/Heart.png");
	
	heart->SetPosition(position);
	heart->Attach<IMovementSystem>(std::move(movementSystem));
	heart->Attach<ICollisionSystem>(std::move(collisionSystem));
	heart->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	heart->Attach<IRenderingSystem>(std::move(renderingSystem));
	
	heart->LoadContent(content);
	heart->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return heart;
}

std::unique_ptr<Powerup> ObjectFactory::CreateWhipPowerup(Vector2 position)
{
	auto whipPowerup = std::make_unique<Powerup>(EntityType::WhipPowerup);

	auto movementSystem = std::make_unique<MovementSystem>(*whipPowerup);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*whipPowerup);
	auto responseSystem = std::make_unique<StaticResponseSystem>(*whipPowerup);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*whipPowerup, "Items/Whip_Powerup.png");

	whipPowerup->SetPosition(position);
	whipPowerup->Attach<IMovementSystem>(std::move(movementSystem));
	whipPowerup->Attach<ICollisionSystem>(std::move(collisionSystem));
	whipPowerup->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	whipPowerup->Attach<IRenderingSystem>(std::move(renderingSystem));
	
	whipPowerup->LoadContent(content);
	whipPowerup->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return whipPowerup;
}
