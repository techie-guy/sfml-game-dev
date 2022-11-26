#include "SceneMenu.hpp"
#include "GameEngine.hpp"
#include "ScenePlay.hpp"

#include <fstream>
#include <sstream>
#include <codecvt>
#include <string>

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
    m_menuText.setCharacterSize(50);

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
        
        sf::String s1 = levelPath;
        sf::String s2 = " " + levelTitle;

        m_levelPaths.push_back(s1);
        m_levelTitles.push_back(s2);
    }

    m_levelTitles[m_selectedMenuIndex].replace(0, 1, L"");

    for(auto& levelTitle : m_levelTitles)
    {
        m_menuStrings.push_back(levelTitle);
    }
    
    for(auto& str : m_menuStrings)
    {
        m_menuText.setString(m_menuText.getString() + str + "\n");
    }

    // Centering the text
    Vec2 textOrigin = Vec2(round(m_menuText.getGlobalBounds().width/2), round(m_menuText.getGlobalBounds().height/2)) + Vec2(round(m_menuText.getLocalBounds().left), round(m_menuText.getLocalBounds().top));
    Vec2 textPosition = Vec2(m_game->window().getSize().x/2, m_game->window().getSize().y/2);

    m_menuText.setOrigin(textOrigin.x, textOrigin.y);
    m_menuText.setPosition(textPosition.x, textPosition.y);
}

void SceneMenu::updateText()
{
    m_menuStrings.clear();
    m_menuText.setString(m_title + "\n");
    
    for(auto& levelTitle : m_levelTitles)
    {
        m_menuStrings.push_back(levelTitle);
    }
    
    for(auto& str : m_menuStrings)
    {
        m_menuText.setString(m_menuText.getString() + str + "\n");
    }
}

void SceneMenu::update()
{
    updateText();
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
            m_previousMenuIndex = m_selectedMenuIndex;
            m_selectedMenuIndex--;
            
            if(m_selectedMenuIndex < 0)
            {
                m_selectedMenuIndex = m_levelTitles.size() - 1;
            }
            
            m_levelTitles[m_previousMenuIndex].replace(0, 1, L" ");
            m_levelTitles[m_selectedMenuIndex].replace(0, 1, L"");
        }
        else if(action.name() == "DOWN")
        {
            m_previousMenuIndex = m_selectedMenuIndex;
            m_selectedMenuIndex++;
            
            if(m_selectedMenuIndex > m_levelTitles.size() - 1)
            {
                m_selectedMenuIndex = 0;
            }

            m_levelTitles[m_previousMenuIndex].replace(0, 1, L" ");
            m_levelTitles[m_selectedMenuIndex].replace(0, 1, L"");
        }
        else if(action.name() == "PLAY")
        {
            m_game->changeScene("PLAY", std::make_shared<ScenePlay>(m_game, m_levelPaths[m_selectedMenuIndex]));
        }
        else if(action.name() == "END")
        {
            onEnd();
        }
    }
}

