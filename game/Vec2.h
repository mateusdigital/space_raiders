//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Vec2,h                                                        //
//  Project   : SpaceRaiders                                                  //
//  Date      : Dec 18, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#pragma once

#include <math.h>

// std
constexpr static float kPI = float(3.14159265359f);
constexpr static float k2PI = float(3.14159265359f * 2.0f);
constexpr static float kDegrees2Radians = (kPI / 180.0f);
constexpr static float kRadians2Degrees = (180.0f / kPI);

struct Vec2
{
    //------------------------------------------------------------------------//
    // Static Functions                                                       //
    //------------------------------------------------------------------------//
    constexpr inline static Vec2 Zero() noexcept { return Vec2{ 0.0f, 0.0f }; }
    constexpr inline static Vec2 One() noexcept { return Vec2{ 1.0f, 1.0f }; }
    constexpr inline static Vec2 Half() noexcept { return Vec2{ 0.5f, 0.5f }; }

    constexpr inline static Vec2 Left() noexcept { return Vec2{ -1.0f,  0.0f }; }
    constexpr inline static Vec2 Right() noexcept { return Vec2{ +1.0f,  0.0f }; }
    constexpr inline static Vec2 Up() noexcept { return Vec2{ 0.0f, -1.0f }; }
    constexpr inline static Vec2 Down() noexcept { return Vec2{ 0.0f, +1.0f }; }


    //------------------------------------------------------------------------//
    // Public Vars                                                            //
    //------------------------------------------------------------------------//
    float x; float y;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
    constexpr explicit Vec2(float x = 0.0f, float y = 0.0f) noexcept :
        x(x), y(y)
    {
        //Empty...
    }

    //------------------------------------------------------------------------//
    // Magnitude                                                              //
    //------------------------------------------------------------------------//
    inline float Magnitude() { return sqrtf(x * x + y * y); }
    inline float MagnitudeSqr() { return       x * x + y * y; }


    //------------------------------------------------------------------------//
    // Distance                                                               //
    //------------------------------------------------------------------------//
    inline float Distance(const Vec2 v2)
    {
        return sqrtf(powf(x - v2.x, 2) + powf(y - v2.y, 2));
    }

    inline float DistanceSqr(const Vec2 v2)
    {
        return powf(x - v2.x, 2) + powf(y - v2.y, 2);
    }


    //------------------------------------------------------------------------//
    // Normalize                                                              //
    //------------------------------------------------------------------------//
    inline void Normalize()
    {
        auto magnitude = Magnitude();
        x /= magnitude; y /= magnitude;
    }

    inline Vec2 Normalized()
    {
        auto vec2 = Vec2(*this);
        vec2.Normalize();

        return vec2;
    }


    //------------------------------------------------------------------------//
    // Rotation                                                               //
    //------------------------------------------------------------------------//
    inline void Rotate(float degrees)
    {
        auto r = (degrees * kDegrees2Radians);
        auto s = sinf(r);
        auto c = cosf(r);

        x = (x * c - y * s);
        y = (x * s + y * c);
    }

    inline Vec2 Rotated(float degrees) const
    {
        auto vec2 = Vec2(*this);
        vec2.Rotate(degrees);

        return vec2;
    }


    //------------------------------------------------------------------------//
    // Operators                                                              //
    //------------------------------------------------------------------------//
    constexpr friend bool operator ==(const Vec2& lhs, const Vec2& rhs);
    constexpr friend bool operator !=(const Vec2& lhs, const Vec2& rhs);

    constexpr friend Vec2 operator +(const Vec2& lhs, const Vec2& rhs);
    constexpr friend Vec2 operator -(const Vec2& lhs, const Vec2& rhs);
    constexpr friend Vec2 operator *(const Vec2& lhs, const Vec2& rhs);
    constexpr friend Vec2 operator /(const Vec2& lhs, const Vec2& rhs);

    constexpr friend Vec2& operator +=(Vec2& lhs, const Vec2& rhs);
    constexpr friend Vec2& operator -=(Vec2& lhs, const Vec2& rhs);
    constexpr friend Vec2& operator *=(Vec2& lhs, const Vec2& rhs);
    constexpr friend Vec2& operator /=(Vec2& lhs, const Vec2& rhs);


    constexpr friend Vec2 operator*(const Vec2& lhs, float scalar);
    constexpr friend Vec2 operator*(float scalar, const Vec2& rhs);

}; //struct Vec2


//----------------------------------------------------------------------------//
// Operators Implementation.                                                  //
//----------------------------------------------------------------------------//
constexpr inline bool operator ==(const Vec2& lhs, const Vec2& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

constexpr inline bool operator !=(const Vec2& lhs, const Vec2& rhs)
{
    return !(lhs == rhs);
}

constexpr inline Vec2 operator +(const Vec2& lhs, const Vec2& rhs)
{
    return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

constexpr inline Vec2 operator -(const Vec2& lhs, const Vec2& rhs)
{
    return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

constexpr inline Vec2 operator *(const Vec2& lhs, const Vec2& rhs)
{
    return Vec2(lhs.x * rhs.x, lhs.y * rhs.y);
}

constexpr inline Vec2 operator /(const Vec2& lhs, const Vec2& rhs)
{
    return Vec2(lhs.x / rhs.x, lhs.y / rhs.y);
}


constexpr inline Vec2& operator +=(Vec2& lhs, const Vec2& rhs)
{
    lhs.x += rhs.x; lhs.y += rhs.y;
    return lhs;
}

constexpr inline Vec2& operator -=(Vec2& lhs, const Vec2& rhs)
{
    lhs.x -= rhs.x; lhs.y -= rhs.y;
    return lhs;
}

constexpr inline Vec2& operator *=(Vec2& lhs, const Vec2& rhs)
{
    lhs.x *= rhs.x; lhs.y *= rhs.y;
    return lhs;
}

constexpr inline Vec2& operator /=(Vec2& lhs, const Vec2& rhs)
{
    lhs.x /= rhs.x; lhs.y /= rhs.y;
    return lhs;
}


constexpr inline Vec2 operator*(const Vec2& lhs, float scalar)
{
    return Vec2(lhs.x * scalar, lhs.y * scalar);
}

constexpr inline Vec2 operator*(float scalar, const Vec2& rhs)
{
    return rhs * scalar;
}
