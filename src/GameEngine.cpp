#include "GameEngine.hpp"
#include "SceneMenu.hpp"
#include "ScenePlay.hpp"

#include <fstream>
#include <sstream>

GameEngine::GameEngine(const std::string& path, const std::string& levelConfigPath)
{
    init(path, levelConfigPath);
}

void GameEngine::init(const std::string& path, const std::string& levelConfigPath)
{
    m_window.create(sf::VideoMode(1280, 720), "2D Game Engine");
    m_window.setVerticalSyncEnabled(true);

    // Loading all the Assets
    std::ifstream assetFile(path);
    std::string asset;
    if(!assetFile.is_open())
    {
        std::cout << "Error Opening Assets File\n";
        exit(EXIT_FAILURE);
    }

    while(getline(assetFile, asset))
    {
        std::istringstream istr(asset);
        std::string str;
        while(istr >> str)
        {
            if(str == "Texture")
            {
                istr >> str;
                std::string textureName = str;
                istr >> str;
                std::string filePath = str;

                m_assets.addTexture(textureName, filePath);
            }
            else if(str == "Animation")
            {
                istr >> str;
                std::string name = str;
                istr >> str;
                std::string textureName = str;
                istr >> str;
                int frameCount = std::stoi(str);
                istr >> str;
                int speed = std::stoi(str);

                Animation animation(name, m_assets.getTexture(textureName), frameCount, speed);
                m_assets.addAnimation(name, animation);
            }
            else if(str == "Font")
            {
                istr >> str;
                std::string fontName = str;
                istr >> str;
                std::string fontPath = str;

                m_assets.addFont(fontName, fontPath);
            }
        }
    }

    changeScene("Menu", std::make_shared<SceneMenu>(this, levelConfigPath));
}

void GameEngine::update()
{
    while (m_running)
    {
        m_window.clear();

        sUserInput();

        m_currentScene->update();

        m_window.display();
    }
}

void GameEngine::run()
{
    update();
    quit();
}

void GameEngine::quit()
{
    m_running = false;
    m_window.close();
}

void GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
    m_currentScene = scene;
    m_sceneMap[sceneName] = scene;
}

void GameEngine::sUserInput()
{
    sf::Event event;

    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_running = false;

        if(event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            if(m_currentScene->actionMap().find(event.key.code) == m_currentScene->actionMap().end())
            {
                continue;
            }

            const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
            m_currentScene->doAction(Action(m_currentScene->actionMap().at(event.key.code), actionType));
        }
    }
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_currentScene;
}

const Assets& GameEngine::assets() const
{
    return m_assets;
}

sf::RenderWindow& GameEngine::window()
{
    return m_window;
}

bool GameEngine::running()
{
    return m_running;
}

std::shared_ptr<Scene> GameEngine::getScene(const std::string& name)
{
    return m_sceneMap.at(name);
}