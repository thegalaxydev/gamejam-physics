#include "AABBColliderComponent.h"
#include "CircleColliderComponent.h"
#include "CContainerColliderComponent.h"
#include <GameMath/Vector3.h>
#include <Raylib/raylib.h>
#include "Project1/TransformComponent.h"
#include "Project1/Engine.h"
#include "Project1/Scene.h"

GamePhysics::AABBColliderComponent::AABBColliderComponent(float width, float height)
{
	m_width = width;
	m_height = height;
	setColliderType(AABB);
}

GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
	GamePhysics::Collision* collisionData = new GamePhysics::Collision();

	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector3 circlePosition = other->getOwner()->getTransform()->getGlobalPosition();

	GameMath::Vector3 direction = circlePosition - position;

	if (direction.x > m_width / 2)
	{
		direction.x = m_width / 2;
	}
	else if (direction.x < -m_width / 2)
	{
		direction.x = -m_width / 2;
	}
	if (direction.y > m_height / 2)
	{
		direction.y = m_height / 2;
	}
	else if (direction.y < -m_height / 2)
	{
		direction.y = -m_height / 2;
	}

	GameMath::Vector3 closestPoint = position + direction;

	GameMath::Vector3 circleToPoint = closestPoint - other->getOwner()->getTransform()->getGlobalPosition();

	float distance = circleToPoint.getMagnitude();

	if (distance > other->getRadius())
	{
		return nullptr;
	}

	collisionData->collider = other;
	collisionData->normal = direction.getNormalized();
	collisionData->contactPoint = closestPoint;
	collisionData->penetrationDistance = other->getRadius() - distance;

	return collisionData;

}

GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	GamePhysics::Collision* collisionData = new GamePhysics::Collision();

	bool isCollision = getRight() > other->getLeft() &&
		getBottom() < other->getTop() &&
		getTop() > other->getBottom() &&
		getLeft() < other->getRight();

	if (!isCollision)
	{
		return nullptr;
	}

	GameMath::Vector3 otherToAABB = other->getOwner()->getTransform()->getGlobalPosition() - getOwner()->getTransform()->getGlobalPosition();

	if (otherToAABB.x > m_width / 2)
	{
		otherToAABB.x = m_width / 2;
	}
	else if (otherToAABB.x < -m_width / 2)
	{
		otherToAABB.x = -m_width / 2;
	}
	if (otherToAABB.y > m_height / 2)
	{
		otherToAABB.y = m_height / 2;
	}
	else if (otherToAABB.y < -m_height / 2)
	{
		otherToAABB.y = -m_height / 2;
	}

	GameMath::Vector3 closestPoint = getOwner()->getTransform()->getGlobalPosition() + otherToAABB;

	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector3 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();

	GameMath::Vector3 direction = otherPosition - position;
	float distance = direction.getMagnitude();

	collisionData->collider = other;
	collisionData->normal = getPenetrationVector(other).getNormalized();
	collisionData->contactPoint = closestPoint;
	collisionData->penetrationDistance = getPenetrationVector(other).getMagnitude();

	return collisionData;
	
}

/// <summary>
/// Checks to see if a collision has occured with a container. If a collision with a container has occured, it uses the container's 'checkCollisionAABB' function and data in order
/// to give accurate collision detection and resolution. 
/// </summary>
/// <param name="other"></param>
/// <returns> The collisionData received from the Container this entity has collided with.</returns>
GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionContainer(CContainerColliderComponent* other)
{
	GamePhysics::Collision* collisionData = other->checkCollisionAABB(this);

	if (!collisionData)
	{
		return nullptr;
	}

	collisionData->collider = other;
	collisionData->normal = collisionData->normal * -1;


	return collisionData;
}

void GamePhysics::AABBColliderComponent::draw()
{
	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

	unsigned int colorCode = getColor();

	RAYLIB_H::DrawRectangleLines(getLeft(), getBottom(), m_width, m_height, GetColor(colorCode));
}

float GamePhysics::AABBColliderComponent::getLeft()
{
	return getOwner()->getTransform()->getGlobalPosition().x - m_width / 2;
}

float GamePhysics::AABBColliderComponent::getRight()
{
	return getOwner()->getTransform()->getGlobalPosition().x + m_width / 2;
	
}

float GamePhysics::AABBColliderComponent::getTop()
{
	return getOwner()->getTransform()->getGlobalPosition().y + m_height / 2;
}

float GamePhysics::AABBColliderComponent::getBottom()
{
	return getOwner()->getTransform()->getGlobalPosition().y - m_height / 2;
}

GameMath::Vector3 GamePhysics::AABBColliderComponent::getPenetrationVector(AABBColliderComponent* other)
{
	float smallestPenetration = abs(getRight() - other->getLeft());

	GameMath::Vector3 normalFace = { 1, 0, 0 };

	if (abs(getLeft() - getRight()) < smallestPenetration)
	{
		smallestPenetration = abs(getLeft() - other->getRight());
		normalFace = { -1, 0, 0 };
	}
	if (abs(getTop() - other->getBottom()) < smallestPenetration)
	{
		smallestPenetration = abs(getTop() - other->getBottom());
		normalFace = { 0, 1, 0 };
	}
	if (abs(getBottom() - other->getTop()) < smallestPenetration)
	{
		smallestPenetration = abs(getBottom() - other->getTop());
		normalFace = { 0, -1, 0 };
	}

	return normalFace * smallestPenetration;
}
