#pragma once
#include "ColliderComponent.h"
namespace GamePhysics
{
	class CircleColliderComponent : public ColliderComponent
	{
	public:
		CircleColliderComponent(float radius) : ColliderComponent() { m_radius = radius; setColliderType(CIRCLE); }

		GamePhysics::Collision* checkCollisionCircle(CircleColliderComponent* other) override;
		GamePhysics::Collision* checkCollisionAABB(AABBColliderComponent* other) override;
		//CircleCollider's override for checking to see if it has collided with a container.
		GamePhysics::Collision* checkCollisionContainer(CContainerColliderComponent* other) override;

		void draw() override;

		float getRadius() { return m_radius; }
		void setRadius(float radius) { m_radius = radius; }

	private:
		float m_radius;
	};
}
