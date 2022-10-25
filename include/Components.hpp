#pragma once

#include "Animation.hpp"
#include "Assets.hpp"

class Component
{
public:
    bool has = false;
};

class CTransform : public Component
{
public:
    Vec2 pos = {0.0f, 0.0f};
    Vec2 prevPos = {0.0f, 0.0f};
    Vec2 scale = {1.0f, 1.0f};
    Vec2 velocity = {0.0f, 0.0f};
    float angle = 0;

    CTransform() {}
    CTransform(const Vec2& p, const Vec2& pp, const Vec2& s, const Vec2& v, float a) :
        pos(p), prevPos(pp), scale(s), velocity(v), angle(a) {}
};

class CBoundingBox : public Component
{
public:
    Vec2 size;
    Vec2 halfSize;

    CBoundingBox() {}
    CBoundingBox(const Vec2& s) : size(s), halfSize(s.x/2, s.y/2) {}
};

class CGravity : public Component
{
public:
    float gravity = 0;
    CGravity() {}
    CGravity(float g) : gravity(g) {}
};

class CState : public Component
{
public:
    std::string state = "idle";
    CState() {}
    CState(const std::string& s) : state(s) {}
};

class CLifeSpan : public Component
{
public:
    int lifespan = 0;
    size_t frameCreated = 0;

    CLifeSpan() {}
    CLifeSpan(int duration, size_t frame) : lifespan(duration), frameCreated(frame) {}
};

class CInput : public Component
{
public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;
    bool canShoot = false;
    bool canJump = false;

    CInput() {}
};

class CAnimation : public Component
{
public:
    Animation animation;
    bool repeat = false;
    CAnimation() {}
    CAnimation(const Animation& a, bool r) : animation(a), repeat(r) {}
};