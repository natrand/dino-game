#include "Obstacles.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>


Obstacles::Obstacles()
{
    // Initialize obstacle properties here
    shape.setSize(sf::Vector2f(30, 30));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(800, 0); // Initial position
    velocity = sf::Vector2f(-200, 0); // Initial velocity
    isActive = false;
    spawnInterval = static_cast<float>(rand() % 2000 + 1000) / 1000.0f;
    timeSinceLastSpawn = 0.0f;
    
}

void Obstacles::update(float deltaTime, float playerVelocityX, const sf::RectangleShape& floor)
{
    if (!isActive)
    {
        timeSinceLastSpawn += deltaTime;
        if (timeSinceLastSpawn > spawnInterval)
        {
            isActive = true;
            shape.setPosition(800, floor.getPosition().y - shape.getSize().y);
            velocityX = -playerVelocityX; // Match player's velocity
            timeSinceLastSpawn = 0.0f;
            spawnInterval = static_cast<float>(rand() % 2000 + 1000) / 1000.0f; // Generate a new spawn interval
        }
    }

    else if (isActive)
    {
        // Update obstacle position based on player velocity and deltaTime
        float newX = shape.getPosition().x + (velocity.x + playerVelocityX) * deltaTime;
        shape.setPosition(newX, shape.getPosition().y);
        float obstacleSpeed = -playerVelocityX; // Match obstacle speed with player speed
        shape.move(obstacleSpeed * deltaTime, 0);
        

        // Deactivate obstacle if it goes off the screen
        if (shape.getPosition().x + shape.getSize().x < 0)
        {
            isActive = false;
        }
    }
}

void Obstacles::draw(sf::RenderWindow& window)
{
    if (isActive)
    {
        window.draw(shape);
    }
}
