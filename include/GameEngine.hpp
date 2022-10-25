#pragma once

#include "Assets.hpp"
#include "Scene.hpp"

#include <SFML/Graphics.hpp>

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine
{
protected:
    sf::RenderWindow m_window;
    Assets m_assets;
    std::shared_ptr<Scene> m_currentScene;
    SceneMap m_sceneMap;
    size_t m_simulationSpeed = 1;
    bool m_running = true;

    void init(const std::string& path, const std::string& levelConfigPath);
    void update();

    void sUserInput();
    std::shared_ptr<Scene> currentScene();

public:
    GameEngine(const std::string& path, const std::string& levelConfigPath);

    void run();
    void quit();

    void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);

    const Assets& assets() const;
    sf::RenderWindow& window();
    bool running();
    std::shared_ptr<Scene> getScene(const std::string& name);
};