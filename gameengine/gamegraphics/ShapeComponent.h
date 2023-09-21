#pragma once
#include "Project1/TransformComponent.h"

namespace GameGraphics
{
    enum ShapeType
    {
        CIRCLE,
        BOX,
        //New shape type made specifically for containers. Makes the same function calls as a CIRCLE ShapeType.
        CIRCLE_CONTAINER
    };
    class ShapeComponent : public GameEngine::Component
    {
    public:
        ShapeComponent(ShapeType shapeType) : Component() { m_shapeType = shapeType; }

        void setColor(unsigned int color) { m_color = color; }
        unsigned int getColor() { return m_color; }

        void setShapeType(ShapeType shapeType) { m_shapeType = shapeType; }
        ShapeType getShapeType() { return m_shapeType; }

        void draw() override;
    private:
        ShapeType m_shapeType;
        unsigned int m_color = 0XFFFFFFFF;
    };
}
