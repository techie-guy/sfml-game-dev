#pragma once

#include <SFML/Graphics.hpp>

#include "Vec2.hpp"

class Animation
{
private:
    sf::Sprite m_sprite;
    std::string m_name = "none";
    size_t m_frameCount = 0;
    size_t m_currentFrame = 0;
    size_t m_speed = 0;
    Vec2 m_size = {1, 1};

public:
    Animation() {};
    Animation(const std::string& name, const sf::Texture& texture, size_t frameCount, size_t speed);

    void update();
    bool hasEnded() const;
    std::string& name();
    size_t frameCount();
    Vec2& size();
    sf::Sprite& sprite();
};