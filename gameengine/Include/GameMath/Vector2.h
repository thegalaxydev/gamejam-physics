#pragma once
namespace GameMath
{
    struct Vector2
    {
        float x;
        float y;

        Vector2();
        Vector2(float x, float y);

        GameMath::Vector2 operator +(GameMath::Vector2 rhs);

        GameMath::Vector2 operator -(GameMath::Vector2 rhs);

        GameMath::Vector2 operator *(float scalar);

        friend GameMath::Vector2 operator *(float scalar, GameMath::Vector2 lhs);

        GameMath::Vector2 operator /(float scalar);

        bool operator ==(GameMath::Vector2 rhs);

        /// <summary>
        /// Returns the length of the vector.
        /// </summary>
        /// <returns></returns>
        float getMagnitude();

        /// <summary>
        /// Returns a copy of this vector normalized.
        /// </summary>
        /// <returns></returns>
        GameMath::Vector2 getNormalized();

        /// <summary>
        /// Returns the normalized version of the vector passed in.
        /// </summary>
        /// <param name="vector">The vector that will be normalized</param>
        /// <returns></returns>
        static GameMath::Vector2 normalize(GameMath::Vector2 vector);

        /// <summary>
        /// Changes this vector to have a magnitude of 1.
        /// </summary>
        GameMath::Vector2 normalize();

        /// <summary>
        /// Returns the dot product of the two vectors given.
        /// </summary>
        /// <param name="lhs"></param>
        /// <param name="rhs"></param>
        /// <returns></returns>
        static float dotProduct(GameMath::Vector2 lhs, GameMath::Vector2 rhs);

        /// <summary>
        /// Finds the angle in radians between the two vectors given. 
        /// </summary>
        /// <param name="lhs"></param>
        /// <param name="rhs"></param>
        /// <returns></returns>
        static float findAngle(GameMath::Vector2 lhs, GameMath::Vector2 rhs);

    };
}


