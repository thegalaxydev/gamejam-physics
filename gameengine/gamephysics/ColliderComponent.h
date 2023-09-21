#pragma once
#include "Project1/Component.h"
#include <GameMath\Vector3.h>

namespace GamePhysics
{
	class CircleColliderComponent;
	class AABBColliderComponent;
	class CContainerColliderComponent;
	class RigidBodyComponent;

	class ColliderComponent : public GameEngine::Component
	{
	public:
		enum ColliderType
		{
			CIRCLE,
			AABB,
			//New collider type made specifically for entities given a ContainerColliderComponent.
			CONTAINER
		};

	public:
		void start() override;
		Collision* checkCollision(ColliderComponent* other);

		virtual Collision* checkCollisionCircle(CircleColliderComponent* other) = 0;
		virtual Collision* checkCollisionAABB(AABBColliderComponent* other) = 0;
		virtual Collision* checkCollisionContainer(CContainerColliderComponent* other) = 0;

		void onCollision(GamePhysics::Collision* other) override;

		void update(double deltaTime) override;

		ColliderType getColliderType() { return m_colliderType; }
		void setColliderType(ColliderType type) { m_colliderType = type; }

		bool getIsTrigger() { return m_isTrigger; }
		void setIsTrigger(bool value) { m_isTrigger = value; }

		unsigned int getColor() { return m_color; }

		RigidBodyComponent* getRigidBody() { return m_rigidBody; }

	private:
		bool m_isTrigger;
		ColliderType m_colliderType;
		unsigned int m_color = 0X00FF00FF;
		RigidBodyComponent* m_rigidBody;
	};

	struct Collision
	{
	public:
		GameMath::Vector3 normal;
		ColliderComponent* collider;
		GameMath::Vector3 contactPoint;
		float penetrationDistance;
	};
}
