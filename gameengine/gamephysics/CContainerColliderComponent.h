#pragma once
#include "ColliderComponent.h"
namespace GamePhysics
{
	class CContainerColliderComponent : public ColliderComponent
	{
	public:
		//Defines what a CContainerColliderComponent is and what arguments it takes in. Also sets the default collider type to be CONTAINER.
		CContainerColliderComponent(float radius) : ColliderComponent() { m_radius = radius; setColliderType(CONTAINER); }

		//Function to determine if collison with a CircleCollider has occurred.
		GamePhysics::Collision* checkCollisionCircle(CircleColliderComponent* other) override;

		//Function to determine if collison with an AABBCollider has occurred.
		GamePhysics::Collision* checkCollisionAABB(AABBColliderComponent* other) override;

		//Function to determine if collison with a CContainerCollider has occurred.
		GamePhysics::Collision* checkCollisionContainer(CContainerColliderComponent* other) override { return nullptr; }

		//Function that gets the container's position and color. Calls RAYLIB's DrawCircleLines() and takes the container's position, radius, and color as arguments.
		void draw() override;

		//Function for getting the radius of the container.
		float getRadius() { return m_radius; }

		//Function that allows you to set the container's radius.
		void setRadius(float radius) { m_radius = radius; }

	private:
		//The container's radius. This variable is needed for drawing, as well as accurate collision detection and resolution.
		float m_radius;
	};
}

