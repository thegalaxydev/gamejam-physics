#pragma once

namespace GameMath
{
    struct Vector2;
    struct Vector3;

    struct Matrix3
    {
    public:

        float m00, m01, m02, m10, m11, m12, m20, m21, m22;

        Matrix3();

        Matrix3(float m11, float m12, float m13,
            float m21, float m22, float m23,
            float  m31, float  m32, float m33);

        GameMath::Matrix3 operator +(GameMath::Matrix3 rhs);

        GameMath::Matrix3 operator -(GameMath::Matrix3 rhs);

        GameMath::Matrix3 operator *(GameMath::Matrix3 rhs);

        GameMath::Vector3 operator *(GameMath::Vector3 rhs);

        bool operator ==(GameMath::Matrix3 rhs);

        /// <summary>
        /// Creates a matrix thats been rotated by the given amount of radians
        ///on the z axis.
        /// </summary>
        /// <returns></returns>
        static GameMath::Matrix3 createRotation(float radians);

        /// <summary>
        /// Creates a matrix thats been rotated by the given amount of radians
        ///on the y axis.
        /// </summary>
        /// <returns></returns>
        static GameMath::Matrix3 createTranslation(GameMath::Vector2 position);

        /// <summary>
        /// Creates a matrix thats been scaled by the given vector.
        /// </summary>
        /// <returns></returns>
        static GameMath::Matrix3 createScale(GameMath::Vector2 scale);
    };
}


