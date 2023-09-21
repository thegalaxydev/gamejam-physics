#pragma once

namespace GameMath
{
    struct Vector4
    {
        float x;
        float y;
        float z;
        float w;

        Vector4();

        Vector4(float x, float y, float z, float w);

        friend GameMath::Vector4 operator *(float scalar, GameMath::Vector4 lhs);

        GameMath::Vector4 operator +(GameMath::Vector4 rhs);

        GameMath::Vector4 operator -(GameMath::Vector4 rhs);

        GameMath::Vector4 operator *(float scalar);

        GameMath::Vector4 operator /(float scalar);

        bool operator == (GameMath::Vector4 rhs);

        /// <summary>
        /// Returns the length of the vector.
        /// </summary>
        /// <returns></returns>
        float getMagnitude();

        /// <summary>
        /// Returns a copy of this vector normalized.
        /// </summary>
        /// <returns></returns>
        GameMath::Vector4 getNormalized();

        /// <summary>
        /// Returns the normalized version of the vector passed in.
        /// </summary>
        /// <param name="vector">The vector that will be normalized</param>
        /// <returns></returns>
        static GameMath::Vector4 normalize(GameMath::Vector4 vector);

        /// <summary>
        /// Changes this vector to have a magnitude of 1.
        /// </summary>
        GameMath::Vector4 normalize();

        /// <summary>
        /// Returns the dot product of the two vectors given.
        /// </summary>
        /// <param name="lhs"></param>
        /// <param name="rhs"></param>
        /// <returns></returns>
        static float dotProduct(GameMath::Vector4 lhs, GameMath::Vector4 rhs);

        /// <summary>
       /// Returns the cross product of the two vectors given.
       /// </summary>
       /// <param name="lhs"></param>
       /// <param name="rhs"></param>
       /// <returns></returns>
        static GameMath::Vector4 crossProduct(GameMath::Vector4 lhs, GameMath::Vector4 rhs);
    };
}


