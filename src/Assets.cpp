#include "Assets.hpp"

void Assets::addTexture(const std::string& name, const std::string& path)
{
    m_textures[name].loadFromFile(path);
}

void Assets::addFont(const std::string& name, const std::string& path)
{
    m_fonts[name].loadFromFile(path);
}

void Assets::addAnimation(const std::string& name, const Animation animation)
{
    m_animations[name] = animation;
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
