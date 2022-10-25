#include "SceneMenu.hpp"
#include "GameEngine.hpp"
#include "ScenePlay.hpp"

#include <fstream>
#include <sstream>

SceneMenu::SceneMenu(GameEngine* gameEngine, const std::string& levelConfigPath) : Scene(gameEngine)
{
    init(levelConfigPath);
}

void SceneMenu::init(const std::string& levelConfigPath)
{
    registerAction(sf::Keyboard::Up, "UP");
    registerAction(sf::Keyboard::Down, "DOWN");
    registerAction(sf::Keyboard::D, "PLAY");
    registerAction(sf::Keyboard::Escape, "END");

    m_menuText.setFont(m_game->assets().getFont("Monocraft"));
    m_title = "The Game";

    // Load levels from the level config file
    std::ifstream levelConfigFile(levelConfigPath);
    std::string level;
    if(!levelConfigFile.is_open())
    {
        std::cout << "Error Opening Level Config File\n";
        exit(EXIT_FAILURE);
    }
    while(getline(levelConfigFile, level))
    {
        std::stringstream levelStream(level);
        std::string levelPath;
        std::string levelTitle;

        levelStream >> levelPath;
        levelTitle = level.substr(levelPath.length()+1);

        m_levelPaths.push_back(levelPath);
        m_levelTitles.push_back(levelTitle);
    }

    // Setting Menu String Vector
    m_menuStrings.push_back(m_title);

    for(auto& levelTitle : m_levelTitles)
    {
        m_menuStrings.push_back(levelTitle);
    }

    // Setting The Menu Text
    for(auto& str : m_menuStrings)
    {
        m_menuText.setString(m_menuText.getString() + str + "\n");
    }
}

void SceneMenu::update()
{
    sRender();
}

void SceneMenu::onEnd()
{
    m_game->quit();
}

void SceneMenu::doAction(const Action& action)
{
    sDoAction(action);
}

void SceneMenu::sRender()
{
    m_entityManager.update();
    m_game->window().draw(m_menuText);
}

void SceneMenu::sDoAction(const Action& action)
{
    if(action.type() == "START")
    {
        if(action.name() == "UP")
        {
            m_selectedMenuIndex--;
            if(m_selectedMenuIndex < 0)
            {
                m_selectedMenuIndex = m_menuStrings.size() - 2;
            }
        }
        else if(action.name() == "DOWN")
        {
            m_selectedMenuIndex++;
            if(m_selectedMenuIndex > m_menuStrings.size() - 2)
            {
                m_selectedMenuIndex = 0;
            }
        }
        else if(action.name() == "PLAY")
        {
            // std::cout << "PLAY\n";
            m_game->changeScene("PLAY", std::make_shared<ScenePlay>(m_game, m_levelPaths[m_selectedMenuIndex]));
        }
        else if(action.name() == "END")
        {
            // std::cout << "END\n";
            onEnd();
        }
    }
}

