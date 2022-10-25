#pragma once

#include <iostream>
#include <math.h>

class Vec2
{
public:
    float x = 0.0f;
    float y = 0.0f;

    Vec2() = default;
    Vec2(float xin, float yin);

    bool operator == (const Vec2& rhs) const;
    bool operator != (const Vec2& rhs) const;

    Vec2 operator + (const Vec2& rhs) const;
    Vec2 operator - (const Vec2& rhs) const;
    Vec2 operator * (const Vec2& rhs) const;
    Vec2 operator / (const Vec2& rhs) const;

    void operator += (const Vec2& rhs);
    void operator -= (const Vec2& rhs);
    void operator *= (const Vec2& rhs);
    void operator /= (const Vec2& rhs);

    float dist(const Vec2& vec) const;
    float length() const;
    Vec2& normalize();
};