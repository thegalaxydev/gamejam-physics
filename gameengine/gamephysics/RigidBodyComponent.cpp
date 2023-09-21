#include "RigidBodyComponent.h"
#include "Project1/TransformComponent.h"
#include "ColliderComponent.h"
#include "Project1/Engine.h"

void GamePhysics::RigidBodyComponent::setVelocity3D(float x, float y, float z)
{
	m_velocity.x = x;
	m_velocity.y = y;
	m_velocity.z = z;
}

void GamePhysics::RigidBodyComponent::setVelocity2D(GameMath::Vector2 velocity)
{
	m_velocity.x = velocity.x;
	m_velocity.y = velocity.y;
}

void GamePhysics::RigidBodyComponent::setVelocity2D(float x, float y)
{
	m_velocity.x = x;
	m_velocity.y = y;
}

float GamePhysics::RigidBodyComponent::getMass()
{
	if (getIsKinematic())
	{
		return INFINITY;
	}

	return m_mass;
}

void GamePhysics::RigidBodyComponent::applyForce(GameMath::Vector3 force)
{
	if (getIsKinematic())
	{
		return;
	}

	setVelocity3D( getVelocity3D() + force / getMass());
}

void GamePhysics::RigidBodyComponent::applyForce(GameMath::Vector2 force)
{
	if (getIsKinematic())
	{
		return;
	}

	setVelocity2D(getVelocity2D() + force / getMass());
}

void GamePhysics::RigidBodyComponent::applyForceToActor(RigidBodyComponent* other, GameMath::Vector3 force)
{
	applyForce(force * -1);
	other->applyForce(force);
}

void GamePhysics::RigidBodyComponent::applyForceToActor(RigidBodyComponent* other, GameMath::Vector2 force)
{
	applyForce(force * -1);
	other->applyForce(force);
}

void GamePhysics::RigidBodyComponent::applyContactForce(GamePhysics::Collision* other)
{
	float mass = getMass();
	float massOther = other->collider->getRigidBody()->getMass();

	float displacement1 = 1;

	float penetrationDistance = other->penetrationDistance;

	if (massOther != INFINITY && !getIsKinematic())
	{
		displacement1 = massOther / (mass + massOther);
	}

	if (!getIsKinematic())
	{
		GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

		getOwner()->getTransform()->setLocalPosition(position + (other->normal * -penetrationDistance));
	}

	float displacement2 = massOther;

	if (mass != INFINITY)
	{
		displacement2 = -(mass / mass + massOther);
	}

	if (!other->collider->getRigidBody()->getIsKinematic())
	{
		GameMath::Vector3 position = other->collider->getOwner()->getTransform()->getGlobalPosition();

		other->collider->getOwner()->getTransform()->setLocalPosition(position + (other->normal * penetrationDistance));
	}
}

void GamePhysics::RigidBodyComponent::resolveCollision(GamePhysics::Collision* collisionData)
{
	applyContactForce(collisionData);
	//Calculate average elasticity
	//average = the sum of e1 and e2 / 2       e= elasticity     j = force magnitude    vA = velocity of obj1    vB = velocity of obj2  n = normal mA = mass of obj1  mB = mass of obj2
	float averageElasticity = (m_elasticity + collisionData->collider->getRigidBody()->m_elasticity) / 2;
	
	// j = (-(1+e) * dot(vA - vB, n)) / (dot(n,n * (1/mA + 1/mB))
	float j = (-(1 + averageElasticity) * GameMath::Vector3::dotProduct(m_velocity - collisionData->collider->getRigidBody()->m_velocity, collisionData->normal)) /
		GameMath::Vector3::dotProduct(collisionData->normal, collisionData->normal * (1 / getMass() + 1 / collisionData->collider->getRigidBody()->getMass()));

	//F = n * -j
	GameMath::Vector3 force = collisionData->normal * -j;

	applyForceToActor(collisionData->collider->getRigidBody(), force);
	
}

void GamePhysics::RigidBodyComponent::fixedUpdate()
{
	double timeStep = GameEngine::Engine::getTimeStep();

	GameMath::Vector3 position = getOwner()->getTransform()->getLocalPosition();
	getOwner()->getTransform()->setLocalPosition(position + getVelocity3D() * timeStep);

	GameMath::Vector3 gravity = { 0, getGravity(), 0 };
	applyForce(gravity * getMass());
}
