#include "ColliderComponent.h"
#include "RigidBodyComponent.h"
#include "Project1/Engine.h"
#include "Project1/Scene.h"

void GamePhysics::ColliderComponent::start()
{
	GameEngine::Engine::getCurrentScene()->addActiveCollider(this);
	m_rigidBody = getOwner()->getComponent<RigidBodyComponent>();
}

GamePhysics::Collision* GamePhysics::ColliderComponent::checkCollision(ColliderComponent* other)
{
	switch (other->getColliderType())
	{
	case CIRCLE:
		return checkCollisionCircle((CircleColliderComponent*)other);

	case AABB:
		return checkCollisionAABB((AABBColliderComponent*)other);
	//New switch statement for when collision detection with a container occurs. Calls the checkCollisionContainer function of the objects detecting the collision.
	case CONTAINER:
		return checkCollisionContainer((CContainerColliderComponent*)other);
	}

	return nullptr;
}

void GamePhysics::ColliderComponent::onCollision(GamePhysics::Collision* other)
{
	m_color = 0XFF0000FF;
}

void GamePhysics::ColliderComponent::update(double deltaTime)
{
	m_color = 0X00FF00FF;
}
