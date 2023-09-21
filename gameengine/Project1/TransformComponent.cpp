#include "TransformComponent.h"

GameMath::Matrix4 GameEngine::TransformComponent::getLocalMatrix()
{
    return m_localMatrix;
}

GameMath::Matrix4 GameEngine::TransformComponent::getGlobalMatrix()
{
    updateMatrices();
    return m_globalMatrix;
}

void GameEngine::TransformComponent::setLocalPosition(GameMath::Vector3 position)
{
    m_translation = position;
}

void GameEngine::TransformComponent::setLocalPosition(float x, float y)
{
    m_translation.x = x;
    m_translation.y = y;
}

GameMath::Vector3 GameEngine::TransformComponent::getLocalPosition()
{
    updateMatrices();
    return m_translation;
}

GameMath::Vector3 GameEngine::TransformComponent::getGlobalPosition()
{
    updateMatrices();
    return GameMath::Vector3(m_globalMatrix.m03, m_globalMatrix.m13, m_globalMatrix.m23);
}

void GameEngine::TransformComponent::setLocalRotation(GameMath::Vector3 rotation)
{
    m_rotation = rotation;
}

GameMath::Vector3 GameEngine::TransformComponent::getLocalRotation()
{
    updateMatrices();
    return m_rotation;
}

void GameEngine::TransformComponent::setLocalScale(GameMath::Vector3 scale)
{
    m_scale = scale;
}

void GameEngine::TransformComponent::setLocalScale(float x, float y)
{
    m_scale.x = x;
    m_scale.y = y;
}

GameMath::Vector3 GameEngine::TransformComponent::getLocalScale()
{
    updateMatrices();
    return m_scale;
}

GameMath::Vector3 GameEngine::TransformComponent::getGlobalScale()
{
    updateMatrices();
    GameMath::Vector3 xAxis = { m_globalMatrix.m00, m_globalMatrix.m01, m_globalMatrix.m02 };
    GameMath::Vector3 yAxis = { m_globalMatrix.m10, m_globalMatrix.m11, m_globalMatrix.m12 };
    GameMath::Vector3 zAxis = { m_globalMatrix.m20, m_globalMatrix.m21, m_globalMatrix.m22 };

    return GameMath::Vector3(xAxis.getMagnitude(), yAxis.getMagnitude(), zAxis.getMagnitude());
}

void GameEngine::TransformComponent::setParent(TransformComponent* parent)
{
    m_parent = parent;
}

GameEngine::TransformComponent* GameEngine::TransformComponent::getParent()
{
    return m_parent;
}

void GameEngine::TransformComponent::updateMatrices()
{
    GameMath::Matrix4 translation = GameMath::Matrix4::createTranslation(m_translation);
    GameMath::Matrix4 rotationX = GameMath::Matrix4::createRotationX(m_rotation.x);
    GameMath::Matrix4 rotationY = GameMath::Matrix4::createRotationY(m_rotation.y);
    GameMath::Matrix4 rotationZ = GameMath::Matrix4::createRotationZ(m_rotation.z);

    GameMath::Matrix4 rotation = rotationX * rotationY * rotationZ;

    GameMath::Matrix4 scale = GameMath::Matrix4::createScale(m_scale);

    m_localMatrix = translation * rotation * scale;

    if (m_parent)
    {
        m_globalMatrix = m_parent->getGlobalMatrix() * m_localMatrix;
    }
    else
    {
        m_globalMatrix = m_localMatrix;
    }
}
