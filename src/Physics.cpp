#include "Physics.hpp"

Vec2 Physics::GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    Vec2 aPos = a->getComponent<CTransform>().pos;
    Vec2 bPos = b->getComponent<CTransform>().pos;
    Vec2 delta = Vec2(abs(aPos.x - bPos.x), abs(aPos.y - bPos.y));
    Vec2 overlap(0.0f, 0.0f);
    overlap.x = (a->getComponent<CBoundingBox>().halfSize.x + b->getComponent<CBoundingBox>().halfSize.x) - delta.x;
    overlap.y = (a->getComponent<CBoundingBox>().halfSize.y + b->getComponent<CBoundingBox>().halfSize.y) - delta.y;

    return overlap;
}

Vec2 Physics::GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    Vec2 aPos = a->getComponent<CTransform>().prevPos;
    Vec2 bPos = b->getComponent<CTransform>().prevPos;
    Vec2 delta = Vec2(abs(aPos.x - bPos.x), abs(aPos.y - bPos.y));
    Vec2 overlap(0.0f, 0.0f);
    overlap.x = (a->getComponent<CBoundingBox>().halfSize.x + b->getComponent<CBoundingBox>().halfSize.x) - delta.x;
    overlap.y = (a->getComponent<CBoundingBox>().halfSize.y + b->getComponent<CBoundingBox>().halfSize.y) - delta.y;

    return overlap;
}