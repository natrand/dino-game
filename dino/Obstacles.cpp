#include "Obstacles.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

sf::Texture obstaclesTexture;

Obstacles::Obstacles()
    : shape(sf::Vector2f(30, 50)), velocity(-300, 0), active(false), velocityX(0.0f), timeSinceLastSpawn(0.0f), spawnInterval(0.0f), obstacleSpacing(20.0f), player()

{
    if (obstaclesTexture.getSize().x == 0) {
        if (!obstaclesTexture.loadFromFile("Assets/dino2.png")) {
            std::cerr << "Error: Image loading failed." << std::endl;
        }
    }
    shape.setTexture(&obstaclesTexture);
    shape.setPosition(800, 0);
    randomizeSpawnInterval();

}

float Obstacles::getX() const {
    return shape.getPosition().x;
}

float Obstacles::getWidth() const {
    return shape.getSize().x;
}

void Obstacles::randomizeSpawnInterval()
{
    spawnInterval = static_cast<float>(rand() % 2000 + 1000) / 1000.0f;
}

bool Obstacles::isActive() const
{
    return active;
}

const sf::RectangleShape& Obstacles::getShape() const
{
    return shape;
}

void Obstacles::startSpawn(const sf::RectangleShape& floor)
{
    active = true;
    shape.setPosition(800, floor.getPosition().y - shape.getSize().y);
    velocityX = -player.getVelocityX();
    randomizeSpawnInterval();
    timeSinceLastSpawn = 0.0f;
}

void Obstacles::updatePosition(float deltaTime)
{
    float newX = shape.getPosition().x + (velocity.x + player.getVelocityX()) * deltaTime;
    shape.setPosition(newX, shape.getPosition().y);
    float obstacleSpeed = -player.getVelocityX();
    shape.move(obstacleSpeed * deltaTime, 0);

    hitbox.left = shape.getPosition().x;
    hitbox.top = shape.getPosition().y;
    hitbox.width = shape.getSize().x;
    hitbox.height = 20;

    sf::FloatRect playerHitbox = player.getRectangle().getGlobalBounds();


    if (playerHitbox.intersects(hitbox)) {

        player.setVelocityX(0);
        player.setGameOver(true);

    }

    if (shape.getPosition().x + shape.getSize().x < -obstacleSpacing)
    {
        active = false;
    }
}

void Obstacles::checkCollisionWithPlayer(Player& player)
{
    if (player.getRectangle().getGlobalBounds().intersects(shape.getGlobalBounds()))
    {
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