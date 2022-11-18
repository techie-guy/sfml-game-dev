#pragma once

#include <SFML/Graphics.hpp>

#include "Vec2.hpp"

class Animation
{
private:
    sf::Sprite m_sprite;
    std::string m_name = "none";
    size_t m_frameCount = 0;
    size_t m_speed = 0;
    Vec2 m_size = {1, 1};

public:
    size_t m_currentFrame = 0;
    Animation() {}
    Animation(const std::string& name, const sf::Texture& texture, size_t frameCount, size_t speed);

    void update();
    bool hasEnded() const;
    const std::string& name() const;
    const size_t frameCount() const;
    const Vec2& size() const;
    sf::Sprite& sprite();
};