#pragma once

#include <vector>
#include <map>
#include <memory>
#include <algorithm>

#include "Entity.hpp"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager
{
private:
    EntityVec m_entities;
    EntityVec m_entitiesToAdd;
    EntityMap m_entityMap;
    size_t m_totalEntities = 0;

    void removeDeadEntites(EntityVec& vec);

public:
    EntityManager();
    void update();
    EntityVec& getEntities();
    EntityVec& getEntities(const std::string& tag);
    std::shared_ptr<Entity> addEntity(const std::string& tag);
};