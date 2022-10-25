#include "Assets.hpp"

void Assets::addTexture(std::string& name, sf::Texture& texture)
{
    m_textures[name] = texture;
}

void Assets::addFont(const std::string& name, sf::Font& font)
{
    m_fonts[name] = font;
}

void Assets::addAnimation(std::string& name, Animation& animation)
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