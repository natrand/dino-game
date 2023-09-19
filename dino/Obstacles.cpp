#include "Obstacles.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>


Obstacles::Obstacles() 
{
    shape.setSize(sf::Vector2f(30, 30));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(800, 0); 
    velocity = sf::Vector2f(-300, 0); 
    active = false;
    velocityX = 0.0f;
    spawnInterval = static_cast<float>(rand() % 2000 + 1000) / 1000.0f;
    timeSinceLastSpawn = 0.0f;
    obstacleSpacing = 20.0f;    
}
bool Obstacles::isActive() const
{
    return active;
}
const sf::RectangleShape& Obstacles::getShape() const
{
    return shape;
}
void Obstacles::update(float deltaTime, float playerVelocityX, const sf::RectangleShape& floor)
{
    if (!active)
    {
        timeSinceLastSpawn += deltaTime*obstacleSpacing;
        if (timeSinceLastSpawn > spawnInterval)
        {
                active = true;
                shape.setPosition(800, floor.getPosition().y - shape.getSize().y);
                velocityX = -playerVelocityX; 
                timeSinceLastSpawn = 0.0f;
                spawnInterval = static_cast<float>(rand() % 2000 + 1000) / 1000.0f;        
        }
    }

    else if (active)
    {
        float newX = shape.getPosition().x + (velocity.x + playerVelocityX) * deltaTime;
        shape.setPosition(newX, shape.getPosition().y);
        float obstacleSpeed = -playerVelocityX;
        shape.move(obstacleSpeed * deltaTime, 0);

        if (shape.getPosition().x + shape.getSize().x < -obstacleSpacing)
        {
            active = false;
        }
    }
    if (player.getRectangle().getGlobalBounds().intersects(shape.getGlobalBounds())) {
        player.setVelocityX(0); 
        player.setGameOver(true); 
    }
}

void Obstacles::draw(sf::RenderWindow& window)
{
    if (active)
    {
        window.draw(shape);
    }
}
