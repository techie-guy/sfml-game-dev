#pragma once

#include "Scene.hpp"

class ScenePlay : public Scene
{
    struct PlayerConfig
    {
        float X, Y, CX, CY, SPEEDX, SPEEDY, MAXSPEED, GRAVITY;
        std::string IDLE;
        std::string RUN;
        std::string JUMP;
        std::string FALL;
        std::string WEAPON;
    };

    enum CameraTypes
    {
        FollowX, FollowXY, Box, Grid, Default
    };

protected:
    std::string m_levelPath;
    std::shared_ptr<Entity> m_player;
    PlayerConfig m_playerConfig;
    bool m_drawTextures = true;
    bool m_drawGrid = false;
    bool m_drawCollision = true;
    int m_cameraType = FollowX;
    const Vec2 m_gridSize = {64, 64};
    sf::Text m_gridText;

    void init(const std::string& m_levelPath);
    void loadLevel(const std::string& filename);
    Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);

    void spawnPlayer();
    void spawnBullet();
    void drawGrid();
    void drawLine(const Vec2& start, const Vec2& end);
    void onEnd();

    void sAnimation();
    void sLifeSpan();
    void sMovement();
    void sEnemySpawner();
    void sCollision();
    void sRender();
    void sCamera();
    void sDoAction(const Action& action);
    void sDebug();

public:
    ScenePlay(GameEngine* gameEngine, const std::string& levelPath);
    void update();
    void doAction(const Action& action);
};
