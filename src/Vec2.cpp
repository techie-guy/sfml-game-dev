#include "Vec2.hpp"

Vec2::Vec2(float xin, float yin)
{
    x = xin;
    y = yin;
}

bool Vec2::operator == (const Vec2& rhs) const
{
    if(x == rhs.x && y == rhs.y) return true;
    return false;
}

bool Vec2::operator != (const Vec2& rhs) const
{
    if(x != rhs.x || y != rhs.y) return true;
    return false;
}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator * (const Vec2& rhs) const
{
    return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator / (const Vec2& rhs) const
{
    return Vec2(x / rhs.x, y / rhs.y);
}

void Vec2::operator += (const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

void Vec2::operator *= (const Vec2& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
}

void Vec2::operator /= (const Vec2& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
}

float Vec2::dist(const Vec2& vec) const
{
    return sqrtf(((x-vec.x)*(x-vec.x) + (y-vec.y)*(y-vec.y)));
}

float Vec2::length() const
{
    return sqrtf(x*x + y*y);
}

Vec2& Vec2::normalize()
{
    float l = length();

    x /= l;
    y /= l;

    return *this;
}