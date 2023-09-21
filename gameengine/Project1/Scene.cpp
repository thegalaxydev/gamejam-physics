#include "Scene.h"
#include "Entity.h"
#include "gamephysics/ColliderComponent.h"
#include "gamephysics/RigidBodyComponent.h"

void GameEngine::Scene::start()
{

	for (Entity* entity : m_entities)
	{
		if (entity->getEnabled())
			entity->start();
	}

	onStart();
}

void GameEngine::Scene::update(double deltaTime)
{
	for (Entity* entity : m_entities)
	{
		if (!entity->getEnabled())
		{
			continue;
		}

		if (!entity->getStarted())
		{
			entity->start();
		}

			entity->update(deltaTime);
	}

	onUpdate(deltaTime);
	
}

void GameEngine::Scene::fixedUpdate()
{
	for (Entity* entity : m_entities)
	{
		if (!entity->getEnabled())
		{
			continue;
		}

		if (!entity->getStarted())
		{
			entity->start();
		}

		entity->fixedUpdate();
	}

	onFixedUpdate();

	for (auto iterator1 = m_activeColliders.begin(); iterator1 != m_activeColliders.end(); iterator1++)
	{
		for (auto iterator2 = iterator1; iterator2 != m_activeColliders.end(); iterator2++)
		{

			GamePhysics::ColliderComponent* collider1 = *iterator1;
			GamePhysics::ColliderComponent* collider2 = *iterator2;

			if (iterator1 == iterator2 || !collider1->getOwner()->getEnabled() || !collider2->getOwner()->getEnabled())
			{
				continue;
			}

			GamePhysics::Collision* collisionData1 = nullptr;
			GamePhysics::Collision* collisionData2 = new GamePhysics::Collision();

			if (collisionData1 = collider1->checkCollision(collider2))
			{
				collider1->getOwner()->onCollision(collisionData1);

				collisionData2->collider = collider1;
				collisionData2->normal = collisionData1->normal * -1;

				collider2->getOwner()->onCollision(collisionData2);

				collider1->getRigidBody()->resolveCollision(collisionData1);
			}
		}
	}

	//onFixedUpdate();
}

void GameEngine::Scene::end()
{
	for (Entity* entity : m_entities)
	{
		if (entity->getEnabled())
			entity->end();
	}

	onEnd();
}

void GameEngine::Scene::draw()
{
	for (Entity* entity : m_entities)
	{
		if (entity->getEnabled())
			entity->draw();
	}

	onDraw();
}

void GameEngine::Scene::addEntity(Entity* entity)
{
	m_entities.add(entity);
}

void GameEngine::Scene::removeEntity(Entity* entity)
{
	m_entities.remove(entity);
}
