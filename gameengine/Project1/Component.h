#pragma once
#include "Entity.h"

namespace GameEngine
{

	class Component
	{
	public:
		Component() { m_enabled = true; }

		virtual void start() {}
		virtual void update(double deltaTime) {}
		virtual void fixedUpdate() {}
		virtual void draw() {}
		virtual void end() {}


		virtual void onEnable() {}
		virtual void onDisable() {}
		virtual void onCollision(GamePhysics::Collision* other) {};

		bool getEnabled() { return m_enabled; }
		void setEnabled(bool enabled);

		Entity* getOwner() { return m_owner; }

	private:
		void setOwner(Entity* entity) { m_owner = entity; }
		bool m_enabled;
		Entity* m_owner = nullptr;

		friend Entity;
	};
}

