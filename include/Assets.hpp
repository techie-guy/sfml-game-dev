#pragma once

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"

class Assets
{
private:
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, Animation> m_animations;
    std::map<std::string, sf::Font> m_fonts;

public:
    Assets() {};

    void addTexture(const std::string& name, const std::string& path);
    void addFont(const std::string& name, const std::string& path);
    void addAnimation(const std::string& name, const Animation animation);

    const sf::Texture& getTexture(const std::string& name) const;
    const Animation& getAnimation(const std::string& name) const;
    const sf::Font& getFont(const std::string& name) const;
};