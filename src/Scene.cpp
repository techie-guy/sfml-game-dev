#include "Scene.hpp"

Scene::Scene(GameEngine* gameEngine)
{
    m_game = gameEngine;
}

void Scene::update()
{
}

void Scene::sDoAction(const Action& action)
{
}

void Scene::sRender()
{
}

void Scene::simulate(const size_t frames)
{
}

void Scene::doAction(const Action& action)
{
}

void Scene::registerAction(int inputKey, const std::string& actionName)
{
    m_actionMap[inputKey] = actionName;
}

// size_t Scene::width() const
// {
// }

// size_t Scene::height() const
// {
// }

void Scene::setPaused(bool paused)
{
    m_paused = paused;
}

size_t Scene::currentFrame() const
{
    return m_currentFrame;
}

bool Scene::hasEnded() const
{
    return m_hasEnded;
}

const ActionMap& Scene::actionMap() const
{
    return m_actionMap;
}

void Scene::drawLine(const Vec2& p1, const Vec2& p2)
{
}