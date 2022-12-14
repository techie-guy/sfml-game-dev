#include "ScenePlay.hpp"
#include "SceneMenu.hpp"
#include "GameEngine.hpp"
#include "Physics.hpp"

#include <fstream>
#include <sstream>
#include <cmath>
#include <SFML/Graphics/Vertex.hpp>

ScenePlay::ScenePlay(GameEngine* gameEngine, const std::string& levelPath) : Scene(gameEngine), m_levelPath(levelPath)
{
    init(levelPath);
}

void ScenePlay::init(const std::string& levelPath)
{
    // register actions
    registerAction(sf::Keyboard::P, "PAUSE");
    registerAction(sf::Keyboard::Escape, "QUIT");
    registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
    registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
    registerAction(sf::Keyboard::G, "TOGGLE_GRID");
    registerAction(sf::Keyboard::Up, "JUMP");
    registerAction(sf::Keyboard::Right, "MOVE_RIGHT");
    registerAction(sf::Keyboard::Left, "MOVE_LEFT");
    registerAction(sf::Keyboard::Space, "SHOOT");

    m_gridText.setCharacterSize(12);
    m_gridText.setFont(m_game->assets().getFont("Monocraft"));

    loadLevel(levelPath);
}

void ScenePlay::loadLevel(const std::string& filename)
{
    m_entityManager = EntityManager();
    std::ifstream levelFile(filename);
    std::string level;
    if(!levelFile.is_open())
    {
        std::cout << "Error Opening Level File: " << filename << "\n";
        exit(EXIT_FAILURE);
    }

    while(getline(levelFile, level))
    {
        std::istringstream istr(level);
        std::string str;
        while(istr >> str)
        {
            if(str == "Tile")
            {
                istr >> str;
                std::string animationName = str;
                istr >> str;
                int x = std::stoi(str);
                istr >> str;
                int y = std::stoi(str);

                auto tile = m_entityManager.addEntity("tile");
                tile->addComponent<CAnimation>(m_game->assets().getAnimation(animationName), true);
                tile->addComponent<CBoundingBox>(tile->getComponent<CAnimation>().animation.size());
                tile->addComponent<CTransform>(gridToMidPixel(x, y, tile), gridToMidPixel(x, y, tile), Vec2(1, 1), Vec2(0, 0), 0);
            }
            else if(str == "Player")
            {
                istr >> str;
                m_playerConfig.X = (float)std::stoi(str);
                istr >> str;
                m_playerConfig.Y = (float)std::stoi(str);
                istr >> str;
                m_playerConfig.CX = (float)std::stoi(str);
                istr >> str;
                m_playerConfig.CY = (float)std::stoi(str);
                istr >> str;
                m_playerConfig.SPEEDX = (float)std::stof(str);
                istr >> str;
                m_playerConfig.SPEEDY = (float)std::stof(str);
                istr >> str;
                m_playerConfig.MAXSPEED = (float)std::stof(str);
                istr >> str;
                m_playerConfig.GRAVITY = (float)std::stof(str);
                istr >> str;
                m_playerConfig.WEAPON = str;
                istr >> str;
                m_playerConfig.IDLE = str;
                istr >> str;
                m_playerConfig.RUN = str;
                istr >> str;
                m_playerConfig.JUMP = str;
                istr >> str;
                m_playerConfig.FALL = str;
            }
        }
    }

    spawnPlayer();
}

Vec2 ScenePlay::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
    Vec2 pos((gridX-1) * m_gridSize.x, gridY * m_gridSize.y);
    Vec2 centerPos = pos + (entity->getComponent<CBoundingBox>().size/Vec2(2.0, 2.0));

    return centerPos;
}

void ScenePlay::onEnd()
{
    m_game->changeScene("Menu", m_game->getScene("Menu"), true);
}

void ScenePlay::update()
{
    m_currentFrame++;
    m_entityManager.update();
    sCamera();
    sMovement();
    sCollision();
    sLifeSpan();
    sAnimation();
    sEnemySpawner();
    sRender();
    sDebug();
}

// Spawners
void ScenePlay::spawnPlayer()
{
    auto player = m_entityManager.addEntity("player");
    player->addComponent<CAnimation>(m_game->assets().getAnimation(m_playerConfig.IDLE), true);
    player->addComponent<CBoundingBox>(Vec2(m_playerConfig.CX, m_playerConfig.CY));
    player->addComponent<CTransform>(gridToMidPixel(m_playerConfig.X, m_playerConfig.Y, player), gridToMidPixel(m_playerConfig.X, m_playerConfig.Y, player), Vec2(1.0f, 1.0f), Vec2(m_playerConfig.SPEEDX, m_playerConfig.SPEEDY), 0);
    player->addComponent<CGravity>(m_playerConfig.GRAVITY);
    player->getComponent<CInput>().canShoot = true;

    m_player = player;
}

void ScenePlay::spawnBullet()
{
    auto bullet = m_entityManager.addEntity("bullet");
    int directionX = m_player->getComponent<CTransform>().scale.x/abs(m_player->getComponent<CTransform>().scale.x);
    bullet->addComponent<CAnimation>(m_game->assets().getAnimation(m_playerConfig.WEAPON), true);
    bullet->addComponent<CTransform>(m_player->getComponent<CTransform>().pos, m_player->getComponent<CTransform>().pos, Vec2(1.0f*directionX, 1.0f), Vec2(10.0f*directionX, 0), 0);
    bullet->addComponent<CBoundingBox>(bullet->getComponent<CAnimation>().animation.size());
    bullet->addComponent<CLifeSpan>(35, m_currentFrame);
}

void ScenePlay::doAction(const Action& action)
{
    sDoAction(action);
}

void ScenePlay::drawGrid()
{
    int rows = (m_game->window().getView().getSize().x + m_game->window().getView().getCenter().x)/m_gridSize.x;
    int cols = (m_game->window().getView().getSize().y + m_game->window().getView().getCenter().y)/m_gridSize.y;

    for(int row = 0; row <= rows; row++)
    {
        drawLine(Vec2(row*m_gridSize.x, 0), Vec2(row*m_gridSize.y, cols*m_gridSize.y));
    }
    
    for(int col = 0; col <= cols; col++)
    {
        drawLine(Vec2(0, col*m_gridSize.y), Vec2(rows*m_gridSize.x, col*m_gridSize.y));
    }
}

void ScenePlay::drawLine(const Vec2& start, const Vec2& end)
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(start.x, start.y)),
        sf::Vertex(sf::Vector2f(end.x, end.y))
    };

    m_game->window().draw(line, 2, sf::Lines);
}

// Systems
void ScenePlay::sAnimation()
{
    if(m_player->getComponent<CState>().state == "run")
    {
        if(m_player->getComponent<CAnimation>().animation.name() != m_game->assets().getAnimation(m_playerConfig.RUN).name())
            m_player->getComponent<CAnimation>().animation = m_game->assets().getAnimation(m_playerConfig.RUN);
    }
    else if(m_player->getComponent<CState>().state == "idle")
    {
        if(m_player->getComponent<CAnimation>().animation.name() != m_game->assets().getAnimation(m_playerConfig.IDLE).name())
            m_player->getComponent<CAnimation>().animation = m_game->assets().getAnimation(m_playerConfig.IDLE);
    }
    else if(m_player->getComponent<CState>().state == "jump")
    {
        if(m_player->getComponent<CAnimation>().animation.name() != m_game->assets().getAnimation(m_playerConfig.JUMP).name())
            m_player->getComponent<CAnimation>().animation = m_game->assets().getAnimation(m_playerConfig.JUMP);
    }
    else if(m_player->getComponent<CState>().state == "fall")
    {
        if(m_player->getComponent<CAnimation>().animation.name() != m_game->assets().getAnimation(m_playerConfig.FALL).name())
            m_player->getComponent<CAnimation>().animation = m_game->assets().getAnimation(m_playerConfig.FALL);
    }

    for(auto& entity : m_entityManager.getEntities())
    {
        entity->getComponent<CAnimation>().animation.sprite().setPosition(entity->getComponent<CTransform>().pos.x, entity->getComponent<CTransform>().pos.y);
        entity->getComponent<CAnimation>().animation.sprite().setScale(entity->getComponent<CTransform>().scale.x, entity->getComponent<CTransform>().scale.y);
        entity->getComponent<CAnimation>().animation.sprite().setRotation(entity->getComponent<CTransform>().angle);
        entity->getComponent<CAnimation>().animation.update();

        if(!entity->getComponent<CAnimation>().repeat)
        {
            if(entity->getComponent<CAnimation>().animation.hasEnded())
                entity->getComponent<CAnimation>().animation = Animation();
        }
    }
}

void ScenePlay::sCamera()
{
    sf::View view = m_game->window().getView();

    if(m_cameraType == FollowX)
    {
        if(m_player->getComponent<CTransform>().pos.x >= m_game->window().getSize().x/2)
        {
            view.setCenter(m_player->getComponent<CTransform>().prevPos.x, m_game->window().getSize().y/2);
        }
    }
    else if(m_cameraType == FollowXY)
    {
        view.setCenter(m_player->getComponent<CTransform>().prevPos.x, m_player->getComponent<CTransform>().prevPos.y);
    }
    else if(m_cameraType == Default)
    {
        view.setCenter(m_game->window().getSize().x/2, m_game->window().getSize().y/2);
    }

    m_game->window().setView(view);
}

void ScenePlay::sMovement()
{
    Vec2 playerVelocity(0, 0);
    if(m_player->getComponent<CInput>().right)
    {
        m_player->getComponent<CState>().state = "run";
        m_player->getComponent<CTransform>().scale.x = 1.0f;
        playerVelocity.x = m_playerConfig.SPEEDX;
    }
    
    if(m_player->getComponent<CInput>().left)
    {
        m_player->getComponent<CState>().state = "run";
        m_player->getComponent<CTransform>().scale.x = -1.0f;
        playerVelocity.x = -m_playerConfig.SPEEDX;
    }
    
    if(m_player->getComponent<CInput>().shoot && m_player->getComponent<CInput>().canShoot)
    {
        spawnBullet();
        m_player->getComponent<CInput>().canShoot = false;
    }

    if(m_player->getComponent<CInput>().up && m_player->getComponent<CInput>().canJump)
    {
        m_player->getComponent<CState>().state = "jump";
        playerVelocity.y = m_playerConfig.SPEEDY;
    }

    if(playerVelocity.x == 0 && playerVelocity.y == 0)
    {
        m_player->getComponent<CState>().state = "idle";
    }

    m_player->getComponent<CTransform>().velocity = playerVelocity;

    for(auto& e : m_entityManager.getEntities())
    {
        if(e->hasComponent<CGravity>())
        {
            e->getComponent<CTransform>().velocity.y += e->getComponent<CGravity>().gravity;
        }

        e->getComponent<CTransform>().prevPos = e->getComponent<CTransform>().pos;
        e->getComponent<CTransform>().pos += e->getComponent<CTransform>().velocity;
    }

    if(m_player->getComponent<CTransform>().velocity.x >= m_playerConfig.MAXSPEED)
    {
        m_player->getComponent<CTransform>().velocity.x = m_playerConfig.MAXSPEED;
    }
    if(m_player->getComponent<CTransform>().velocity.y >= m_playerConfig.MAXSPEED)
    {
        m_player->getComponent<CTransform>().velocity.y = m_playerConfig.MAXSPEED;
    }
}

void ScenePlay::sLifeSpan()
{
    for(auto& entity : m_entityManager.getEntities())
    {
        if(entity->hasComponent<CLifeSpan>())
        {
            if((m_currentFrame - entity->getComponent<CLifeSpan>().frameCreated) > entity->getComponent<CLifeSpan>().lifespan)
            {
                entity->destroy();
                if(entity->tag() == "bullet")
                {
                    m_player->getComponent<CInput>().canShoot = true;
                }
            }
        }
    }
}

void ScenePlay::sEnemySpawner()
{
}

void ScenePlay::sCollision()
{
    for(auto& tile : m_entityManager.getEntities("tile"))
    {
        Vec2 previousOverlap = Physics::GetPreviousOverlap(m_player, tile);
        Vec2 currentOverlap = Physics::GetOverlap(m_player, tile);

        // std::cout << m_player->getComponent<CTransform>().pos << "\n";

        // std::cout << "Current Overlap: " << currentOverlap << "\n";
        // std::cout << "Previous Overlap: " << previousOverlap << "\n";
        if(previousOverlap.x > 0)
        {
            if(currentOverlap.y > 0)
            {
                if(m_player->getComponent<CTransform>().pos.y < tile->getComponent<CTransform>().pos.y)
                {
                    m_player->getComponent<CInput>().canJump = true;
                    m_player->getComponent<CTransform>().pos.y -= currentOverlap.y;
                    m_player->getComponent<CTransform>().velocity.y = 0;
                    if(m_player->getComponent<CTransform>().velocity.x == 0)
                        m_player->getComponent<CState>().state = "idle";
                }
                else if(m_player->getComponent<CTransform>().pos.y > tile->getComponent<CTransform>().pos.y)
                {
                    tile->destroy();
                    m_player->getComponent<CTransform>().pos.y += currentOverlap.y;
                    m_player->getComponent<CInput>().canJump = false;
                    m_player->getComponent<CTransform>().velocity.y = 0;
                    if(m_player->getComponent<CTransform>().velocity.x == 0)
                        m_player->getComponent<CState>().state = "idle";
                }
            }
            // else
            // {
            //     if(m_player->getComponent<CTransform>().velocity.y > 0)
            //     {
            //         m_player->getComponent<CInput>().canJump = true;
            //         m_player->getComponent<CState>().state = "fall";
            //     }
            // }

            // Fall if:
            // 1. Player not touching ground
            // 2. Player not jumping
        }
        else if(previousOverlap.y > 0)
        {
            if(currentOverlap.x > 0)
            {
                if(m_player->getComponent<CTransform>().pos.x < tile->getComponent<CTransform>().pos.x)
                {
                    m_player->getComponent<CTransform>().pos.x -= currentOverlap.x;
                }
                else if(m_player->getComponent<CTransform>().pos.x > tile->getComponent<CTransform>().pos.x)
                {
                    m_player->getComponent<CTransform>().pos.x += currentOverlap.x;
                }
            }
        }

        if(!(currentOverlap.x > 0 && currentOverlap.y > 0))
        {
            if(m_player->getComponent<CTransform>().velocity.y > 0 && (m_player->getComponent<CTransform>().pos.x == m_player->getComponent<CTransform>().prevPos.x))
            {
                m_player->getComponent<CInput>().canJump = false;
                m_player->getComponent<CState>().state = "fall";
            }
        }

        if(m_player->getComponent<CTransform>().pos.y > m_game->window().getView().getSize().y)
        {
            m_game->changeScene("Menu", m_game->getScene("Menu"));
        }

        for(auto& bullet : m_entityManager.getEntities("bullet"))
        {
            Vec2 bulletOverlap = Physics::GetOverlap(bullet, tile);
            if(bulletOverlap.x >= 0 && bulletOverlap.y >= 0)
            {
                bullet->destroy();
                tile->destroy();
                m_player->getComponent<CInput>().canShoot = true;
            }
        }
    }
}

void ScenePlay::sRender()
{
    for(auto& entity : m_entityManager.getEntities())
    {
        if(m_drawTextures)
        {
            m_game->window().draw(entity->getComponent<CAnimation>().animation.sprite());
        }
        if(m_drawCollision)
        {
            sf::RectangleShape hitbox;
            hitbox.setSize(sf::Vector2f(entity->getComponent<CBoundingBox>().size.x, entity->getComponent<CBoundingBox>().size.y));
            hitbox.setOutlineColor(sf::Color::Red);
            hitbox.setOutlineThickness(3);
            hitbox.setFillColor(sf::Color(0, 0, 0, 0));
            hitbox.setPosition(entity->getComponent<CTransform>().pos.x-entity->getComponent<CBoundingBox>().halfSize.x, entity->getComponent<CTransform>().pos.y-entity->getComponent<CBoundingBox>().halfSize.y);
            m_game->window().draw(hitbox);
        }
    }
    if(m_drawGrid)
    {
        drawGrid();
    }
}

void ScenePlay::sDoAction(const Action& action)
{
    if(action.type() == "START")
    {
        if(action.name() == "TOGGLE_TEXTURE")
        {
            m_drawTextures = !m_drawTextures;
        }
        else if(action.name() == "TOGGLE_COLLISION")
        {
            m_drawCollision = !m_drawCollision;
        }
        else if(action.name() == "TOGGLE_GRID")
        {
            m_drawGrid = !m_drawGrid;
        }
        else if(action.name() == "PAUSE")
        {
            setPaused(!m_paused);
        }
        else if(action.name() == "QUIT")
        {
            onEnd();
        }
        else if(action.name() == "JUMP")
        {
            m_player->getComponent<CInput>().up = true;
        }
        else if(action.name() == "MOVE_RIGHT")
        {
            m_player->getComponent<CInput>().right = true;
        }
        else if(action.name() == "MOVE_LEFT")
        {
            m_player->getComponent<CInput>().left = true;
        }
        else if(action.name() == "SHOOT")
        {
            m_player->getComponent<CInput>().shoot = true;
        }
    }
    else if(action.type() == "END")
    {
        if(action.name() == "JUMP")
        {
            m_player->getComponent<CInput>().up = false;
        }
        else if(action.name() == "MOVE_RIGHT")
        {
            m_player->getComponent<CInput>().right = false;
        }
        else if(action.name() == "MOVE_LEFT")
        {
            m_player->getComponent<CInput>().left = false;
        }
        else if(action.name() == "SHOOT")
        {
            m_player->getComponent<CInput>().shoot = false;
        }
    }
}

void ScenePlay::sDebug()
{
    // std::cout << m_player->getComponent<CState>().state << "\n";
}
