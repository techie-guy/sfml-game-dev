#include "Entity.hpp"

Entity::Entity(const std::string& tag, const size_t id) : m_tag(tag), m_id(id)
{
}

void Entity::destroy()
{
    m_isActive = false;
}

const std::string& Entity::tag() const
{
    return m_tag;
}

const bool Entity::isActive() const
{
    return m_isActive;
}

const size_t Entity::id() const
{
    return m_id;
}