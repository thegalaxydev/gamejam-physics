#pragma once

namespace GameMath
{
    struct Vector3
    {
        float x;
        float y;
        float z;

        Vector3();
        Vector3(float x, float y, float z);

        GameMath::Vector3 operator +(GameMath::Vector3 rhs);

        GameMath::Vector3 operator -(GameMath::Vector3 rhs);

        GameMath::Vector3 operator *(float scalar);

        friend GameMath::Vector3 operator *(float scalar, GameMath::Vector3 lhs);

        GameMath::Vector3 operator /(float scalar);

        bool operator ==(GameMath::Vector3 rhs);

        /// <summary>
        /// Returns the length of the vector.
        /// </summary>
        /// <returns></returns>
        float getMagnitude();

        /// <summary>
        /// Returns a copy of this vector normalized.
        /// </summary>
        /// <returns></returns>
        GameMath::Vector3 getNormalized();

        /// <summary>
        /// Returns the normalized version of a the vector passed in.
        /// </summary>
        /// <param name="vector">The vector that will be normalized</param>
        /// <returns></returns>
        static GameMath::Vector3 normalize(GameMath::Vector3 vector);

        /// <summary>
        /// Changes this vector to have a magnitude of 1.
        /// </summary>
        GameMath::Vector3 normalize();

        /// <summary>
        /// Returns the dot product of the two vectors given.
        /// </summary>
        /// <param name="lhs"></param>
        /// <param name="rhs"></param>
        /// <returns></returns>
        static float dotProduct(GameMath::Vector3 lhs, GameMath::Vector3 rhs);

        /// <summary>
        /// Returns the cross product of the two vectors given.
        /// </summary>
        /// <param name="lhs"></param>
        /// <param name="rhs"></param>
        /// <returns></returns>
        static GameMath::Vector3 crossProduct(GameMath::Vector3 lhs, GameMath::Vector3 rhs);

    };
}


