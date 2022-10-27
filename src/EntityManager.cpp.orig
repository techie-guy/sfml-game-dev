#include "EntityManager.hpp"

EntityManager::EntityManager()
{
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
    m_entitiesToAdd.push_back(e);

    return e;
}

EntityVec& EntityManager::getEntities()
{
    return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
    return m_entityMap[tag];
}

void EntityManager::removeDeadEntites(EntityVec& vec)
{
    auto deadEntities = std::remove_if(vec.begin(), vec.end(), [](std::shared_ptr<Entity>& entity) { return entity->isActive() == false; });
    vec.erase(deadEntities, vec.end());
}

void EntityManager::update()
{
    for(auto& e : m_entitiesToAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }

    // If e is dead, remove it
    removeDeadEntites(m_entities);

    for(auto& [tag, entityVec] : m_entityMap)
    {
        removeDeadEntites(entityVec);
    }

    m_entitiesToAdd.clear();
}