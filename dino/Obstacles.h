#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Obstacles
{
public:
    Obstacles();
    void draw(sf::RenderWindow& window);
    bool isActive() const;
    const sf::RectangleShape& getShape() const;
    void startSpawn(const sf::RectangleShape& floor);
    void updatePosition(float deltaTime);
    void checkCollisionWithPlayer(Player& player);
    float getX() const;
    float getWidth() const;

private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::FloatRect hitbox;
    bool active;
    float velocityX;
    float timeSinceLastSpawn;
    float spawnInterval;
    float obstacleSpacing;
    Player player;
    void randomizeSpawnInterval();


};