#pragma once

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>

#include "Animation.hpp"

class Assets
{
private:
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, Animation> m_animations;
    std::map<std::string, sf::Font> m_fonts;
    // std::map<std::string, sf::Sound> m_sounds;

public:
    Assets() {};
    
    void addTexture(std::string const& name, std::string const& path);
    void addAnimation(std::string const& name, std::string const& textureName, int frameCount, int speed);
    void addFont(std::string const& name, std::string const& path);
    // void addSound(std::string& name, sf::Sound& sound);

    const sf::Texture& getTexture(const std::string& name) const;
    const Animation& getAnimation(const std::string& name) const;
    const sf::Font& getFont(const std::string& name) const;
    // sf::Sound& getSound(std::string& name);
};