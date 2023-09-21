#pragma once
#include "Component.h"
#include <GameMath/Matrix4.h>
#include <GameMath/Vector3.h>

namespace GameEngine
{
    class TransformComponent :
        public Component
    {
    public:
        GameMath::Matrix4 getLocalMatrix();
        GameMath::Matrix4 getGlobalMatrix();

        void setLocalPosition(GameMath::Vector3 position);
        void setLocalPosition(float x, float y);

        GameMath::Vector3 getLocalPosition();
        GameMath::Vector3 getGlobalPosition();

        void setLocalRotation(GameMath::Vector3 rotation);
        GameMath::Vector3 getLocalRotation();

        void setLocalScale(GameMath::Vector3 scale);
        void setLocalScale(float x, float y);
        GameMath::Vector3 getLocalScale();

        GameMath::Vector3 getGlobalScale();

        void setParent(TransformComponent* parent);
        TransformComponent* getParent();

    private:
        void updateMatrices();

    private:
        GameMath::Matrix4 m_localMatrix;
        GameMath::Matrix4 m_globalMatrix;

        GameMath::Vector3 m_translation = GameMath::Vector3{ 0.0f, 0.0f, 0.0f };
        GameMath::Vector3 m_rotation = GameMath::Vector3{ 0.0f, 0.0f, 0.0f };
        GameMath::Vector3 m_scale = GameMath::Vector3{ 1.0f, 1.0f, 1.0f };

        TransformComponent* m_parent = nullptr;
    };
}
