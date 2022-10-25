#include "Animation.hpp"

Animation::Animation(const std::string& name, const sf::Texture& texture, size_t frameCount, size_t speed) : m_name(name), m_frameCount(frameCount), m_speed(speed)
{
    m_size = Vec2(texture.getSize().x / frameCount, texture.getSize().y);
    m_sprite.setOrigin(m_size.x / 2.0f, m_size.y / 2.0f);
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(sf::IntRect(std::floor(m_currentFrame) * m_size.x, 0, m_size.x, m_size.y));
}

void Animation::update()
{
    m_currentFrame++;
    int animFrame = (m_currentFrame / m_speed) % m_frameCount;
    sf::IntRect rectangle(animFrame*m_size.x, 0, m_size.x, m_size.y);
    m_sprite.setTextureRect(rectangle);
}

bool Animation::hasEnded() const
{
    return m_currentFrame > m_frameCount;
}

std::string& Animation::name()
{
    return m_name;
}

size_t Animation::frameCount()
{
    return m_frameCount;
}

Vec2& Animation::size()
{
    return m_size;
}

sf::Sprite& Animation::sprite()
{
    return m_sprite;
}
