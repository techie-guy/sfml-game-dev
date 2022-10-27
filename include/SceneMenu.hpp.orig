#pragma once

#include "Scene.hpp"
#include <map>
#include <memory>
#include <deque>

class SceneMenu : public Scene
{
protected:
    std::string m_title;
    std::vector<std::string> m_menuStrings;
    std::vector<std::string> m_levelPaths;
    std::vector<std::string> m_levelTitles;
    sf::Text m_menuText;
    int m_selectedMenuIndex = 0;

    void init(const std::string& levelConfigPath);
    void update();
    void onEnd();
    
    void sRender();
    void sDoAction(const Action& action);

public:
    SceneMenu(GameEngine* gameEngine, const std::string& levelConfigPath);
    void doAction(const Action& action);
};