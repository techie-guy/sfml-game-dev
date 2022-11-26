#pragma once

#include "Scene.hpp"
#include <map>
#include <memory>
#include <deque>

#include <SFML/System/String.hpp>

class SceneMenu : public Scene
{
protected:
    sf::String m_title = "Cool Game";
    std::vector<sf::String> m_menuStrings;
    std::vector<sf::String> m_levelPaths;
    std::vector<sf::String> m_levelTitles;
    sf::Text m_menuText;
    int m_selectedMenuIndex = 0;
    int m_previousMenuIndex = 0;

    void init(const std::string& levelConfigPath);
    void update();
    void onEnd();
    void updateText();

    void sRender();
    void sDoAction(const Action& action);

public:
    SceneMenu(GameEngine* gameEngine, const std::string& levelConfigPath);
    void doAction(const Action& action);
};
