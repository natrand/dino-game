#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Obstacles
{
public:
    Obstacles();
    void update(float deltaTime, float playerVelocityX, const sf::RectangleShape& floor);
    void draw(sf::RenderWindow& window);
    bool isActive() const;
    const sf::RectangleShape& getShape() const; 

private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    bool active;
    float velocityX;
    float timeSinceLastSpawn;
    float spawnInterval;
    
    float obstacleSpacing;
    Player player;
    
};
