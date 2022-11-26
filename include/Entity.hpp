#pragma once

#include "Components.hpp"

#include <tuple>
#include <string>

class EntityManager;

typedef std::tuple<CTransform, CBoundingBox, CLifeSpan, CInput, CAnimation, CGravity, CState> ComponentTuple;

class Entity
{
private:
    friend class EntityManager;

    bool m_isActive = true;
    std::string m_tag = "default";
    size_t m_id = 0;
    ComponentTuple m_components;

    Entity(const std::string& tag, const size_t id);

public:
    void destroy();
    const size_t id() const;
    const bool isActive() const;
    const std::string& tag() const;

    template<typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        auto& component = getComponent<T>();
        component = T(std::forward<TArgs>(mArgs)...);
        component.has = true;
        return component;
    }

    template<typename T>
    T& getComponent()
    {
        return std::get<T>(m_components);
    }

    template<typename T>
    bool hasComponent()
    {
        return getComponent<T>().has;
    }

    template<typename T>
    void removeComponent()
    {
        getComponent<T>() = T();
    }
};
