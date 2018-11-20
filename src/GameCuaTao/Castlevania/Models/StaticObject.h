#pragma once

#include "GameObject.h"
#include "Systems/Rendering/ISpriteRenderingSystem.h"

namespace Castlevania
{
	class StaticObject : public GameObject
	{
	public:
		StaticObject();
		StaticObject(EntityType type);

		RectF GetFrameRect();
		RectF GetBoundingBox() override;
		Sprite &GetSprite();

		template<typename T>
		void AttachRenderer(std::unique_ptr<T> system);

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime, ObjectCollection *objectCollection = nullptr) override;
		void Draw(SpriteExtensions &spriteBatch) override;

		~StaticObject();

		std::unique_ptr<ISpriteRenderingSystem> renderingSystem;
	};
}