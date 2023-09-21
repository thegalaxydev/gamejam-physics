#pragma once
#include "List.h"

namespace GamePhysics
{
    struct Collision;
}

namespace GameEngine
{
	class Component;
    class TransformComponent;

    class Entity
    {
    public:
        Entity();

        void start(); 
        void update(double deltaTime);
        void fixedUpdate();
        void end();
        void draw();

        virtual void onStart() {}
        virtual void onUpdate(double deltaTime) {}
        virtual void onFixedUpdate() {}
        virtual void onEnd() {}
        virtual void onDraw() {}
        virtual void onEnable() {}
        virtual void onDisable() {}
        virtual void onCollision(GamePhysics::Collision* other);

        void addComponent(Component* component);
        
        template<typename T>
        T* addComponent();

        template<typename T>
        T* getComponent();

        bool getStarted() { return m_started; }
        TransformComponent* getTransform() { return m_transform; }

        bool getEnabled() { return m_enabled; };
        void setEnabled(bool value);

    private:
        bool m_enabled = true;
        bool m_started;
        List<Component*> m_components;
        TransformComponent* m_transform;
    };

    template<typename T>
    inline T* Entity::addComponent()
    {
        Component* component = new T();

        component->setOwner(this);
        m_components.add(component);

        return (T*)component;
    }

    template<typename T>
    inline T* Entity::getComponent()
    {
        T* result = nullptr;

        for (Component* component : m_components)
        {
            if (result = dynamic_cast<T*>(component))
            {
                break;
            }
        }
        return result;
    }
}

