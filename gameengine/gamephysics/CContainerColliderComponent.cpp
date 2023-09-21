#include "CContainerColliderComponent.h"
#include "CircleColliderComponent.h"
#include "AABBColliderComponent.h"
#include <GameMath/Vector3.h>
#include "Project1/TransformComponent.h"
#include <Raylib/raylib.h>

GamePhysics::Collision* GamePhysics::CContainerColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
    //Owner's position
	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();
	//Other's position - the circle collider of the other entity.
    GameMath::Vector3 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();

	//Finds a vector named 'direction', by subtracting the owner's position from the other's position.
    GameMath::Vector3 direction = otherPosition - position;
	//'direction' is then converted into a float named 'distance' by getting the magnitude of 'direction'.
    float distance = direction.getMagnitude();

    //An if statement that says as long as 'distance' is less than or equal to the owner's radius (container) minus the other's radius, then a collision has NOT occurred.
	if (distance <= getRadius() - other->getRadius())
    {
        return nullptr;
    }

    //New variable that represents a collision
	GamePhysics::Collision* collisionData = new GamePhysics::Collision();

    //We set the collider we're looking at for information to be other.
	collisionData->collider = other;

	//We set the normal to be 'direction' after it has been normalized.
    collisionData->normal = direction.getNormalized();

	//Find's the closest/ most accurate point that a collision is occurring in a container.
    collisionData->contactPoint = getOwner()->getTransform()->getGlobalPosition() + direction.getNormalized() * getRadius();

	//Gives the smallest distance that two colliders overlap.
    collisionData->penetrationDistance = getRadius() - other->getRadius() - distance;

    return collisionData;
}

GamePhysics::Collision* GamePhysics::CContainerColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	//Creates a variable to represent a collision
	GamePhysics::Collision* collisionData = new GamePhysics::Collision();

	//If a collision has not occurred, return nullptr.
	if (!collisionData)
	{
		return nullptr;
	}

	//Gets the position of other.
	GameMath::Vector3 position = other->getOwner()->getTransform()->getGlobalPosition();
	//Gets the owner's/container's position.
	GameMath::Vector3 circlePosition = getOwner()->getTransform()->getGlobalPosition();

	//Finds the direction vector by subtracting the container's position from the AABB's position.
	GameMath::Vector3 direction = position - circlePosition;


	//If statements that set the parameters of when a collision has occurred with an AABB, then clamps the direction variable so that it stays within the scale of the AABB on
	//it's x and y axis.
	if (direction.x > other->getWidth())
	{
		direction.x = other->getWidth() / 2;
	}
	else if (direction.x < -other->getWidth() / 2)
	{
		direction.x = -other->getWidth() / 2;
	}
	if (direction.y > other->getHeight() / 2)
	{
		direction.y = other->getHeight() / 2;
	}
	else if (direction.y < -other->getHeight() / 2)
	{
		direction.y = -other->getHeight() / 2;
	}

	//Creates a new vector named closestPoint by adding position and direction. 
	GameMath::Vector3 closestPoint = position + direction;

	GameMath::Vector3 circleToPoint = closestPoint - circlePosition;

	float distance = circleToPoint.getMagnitude();

	if (distance <= getRadius())
	{
		return nullptr;
	}

	collisionData->collider = other;
	collisionData->normal = direction.getNormalized();
	collisionData->contactPoint = closestPoint;
	collisionData->penetrationDistance = getRadius() - distance;

	return collisionData;
}

void GamePhysics::CContainerColliderComponent::draw()
{
    GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

    unsigned int colorCode = getColor();

    RAYLIB_H::DrawCircleLines(position.x, position.y, getRadius(), GetColor(colorCode));
}
