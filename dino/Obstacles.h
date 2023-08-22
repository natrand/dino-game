#pragma once

#include <SFML/Graphics.hpp>


class Obstacles
{
public:
    Obstacles();
    void update(float deltaTime, float playerVelocityX, const sf::RectangleShape& floor);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    bool isActive;
    float velocityX;
    float timeSinceLastSpawn;
    float spawnInterval;
};
