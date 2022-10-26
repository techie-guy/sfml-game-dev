#include "Assets.hpp"

void Assets::addTexture(std::string const& name, std::string const& path)
{
    m_textures[name].loadFromFile(path);
}

void Assets::addFont(std::string const& name, std::string const& path)
{
    m_fonts[name].loadFromFile(path);
}

void Assets::addAnimation(std::string const& name, std::string const& textureName, int frameCount, int speed)
{
    m_animations[name] = Animation(name, getTexture(textureName), frameCount, speed);
}

const sf::Texture& Assets::getTexture(const std::string& name) const
{
    return m_textures.at(name);
}

const Animation& Assets::getAnimation(const std::string& name) const
{
    return m_animations.at(name);
}

const sf::Font& Assets::getFont(const std::string& name) const
{
    return m_fonts.at(name);
}