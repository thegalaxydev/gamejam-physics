#include "CircleColliderComponent.h"
#include "AABBColliderComponent.h"
#include "CContainerColliderComponent.h"
#include <GameMath/Vector3.h>
#include "Project1/TransformComponent.h"
#include <Raylib/raylib.h>

GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
    GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector3 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();

    GameMath::Vector3 direction = otherPosition - position;
    float distance = direction.getMagnitude();

    if (distance > other->getRadius() + getRadius())
    {
        return nullptr;
    }

    GamePhysics::Collision* collisionData = new GamePhysics::Collision();

    collisionData->collider = other;
    collisionData->normal = direction.getNormalized();
    collisionData->contactPoint = getOwner()->getTransform()->getGlobalPosition() + direction.getNormalized() * getRadius();
    collisionData->penetrationDistance = other->getRadius() + getRadius() - distance;

    return collisionData;
}

GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
    GamePhysics::Collision* collisionData = other->checkCollisionCircle(this);

    if (!collisionData)
    {
        return nullptr;
    }

    GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector3 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();

    GameMath::Vector3 direction = otherPosition - position;
    float distance = direction.getMagnitude();

    collisionData->collider = other;
    collisionData->normal = direction.getNormalized();


    return collisionData;
}

/// <summary>
/// Checks to see if a collision has occured with a container. If a collision with a container has occured, it uses the container's 'checkCollisionCircle' function and data in order
/// to give accurate collision detection and resolution. 
/// </summary>
/// <param name="other"></param>
/// <returns> The collisionData received from the Container this entity has collided with.</returns>
GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionContainer(CContainerColliderComponent* other)
{
    GamePhysics::Collision* collisionData = other->checkCollisionCircle(this);

    if (!collisionData)
    {
        return nullptr;
    }

    collisionData->collider = other;
    collisionData->normal = collisionData->normal * -1;


    return collisionData;
}

void GamePhysics::CircleColliderComponent::draw()
{
    GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

    unsigned int colorCode = getColor();

    RAYLIB_H::DrawCircleLines(position.x, position.y, getRadius(), GetColor(colorCode));
}
