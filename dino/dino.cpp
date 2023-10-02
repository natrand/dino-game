#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Player.h"
#include "Obstacles.h"



int main()
{


    sf::RenderWindow window(sf::VideoMode(800, 600), "Dino Game");
    sf::Event ev;
    sf::View view(sf::FloatRect(0.f, 0.f, 800.f, 600.f));

    sf::RectangleShape floor;
    floor.setSize(sf::Vector2f(window.getSize().x, 40));
    floor.setFillColor(sf::Color::Green);
    floor.setPosition(0, window.getSize().y - floor.getSize().y);


    window.setFramerateLimit(60);
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(50, 50));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(0, window.getSize().y - rectangle.getSize().y);


    Player player;
    const int maxObstacles = 5;
    Obstacles obstacles[maxObstacles];




    bool gameStarted = false;
    bool gameOver = false;
    float jumpHeight = 200.0f;
    float jumpSpeedY = -25.0f;
    bool canJump = false;


    //text
    /*
    sf::Text gameOverText; // Create a text object
    gameOverText.setFont(sf::Font()); // Set the font
    gameOverText.setCharacterSize(48); // Set the character size
    gameOverText.setString("Game Over"); // Set the text content
    gameOverText.setPosition(300, 200); // Set the position
    gameOverText.setFillColor(sf::Color::Red); // Set the text color
    */

    while (window.isOpen() && !gameOver)
    {
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape)
                    window.close();

                else if (ev.key.code == sf::Keyboard::Space && canJump)
                {
                    player.jump();
                    player.update(window);
                    player.setVelocityY(jumpSpeedY);
                    player.startGame();

                    gameStarted = true;
                    canJump = true;
                }
                break;
            case sf::Event::KeyReleased:
                if (ev.key.code == sf::Keyboard::Space) {
                    canJump = false;
                }
                break;
            }
        }
        if (player.getY() >= window.getSize().y - floor.getSize().y - jumpHeight)
        {
            canJump = true;
        }

        float moveAmount = 0.25f;
        float backgroundSpeed = 5.f;


        player.update(window);
        player.updatePosition(1.0f / 60.0f);

        if (player.getX() + player.getWidth() >= view.getCenter().x + view.getSize().x / 2)
        {
            float playerVelocityX = player.getVelocityX();
            view.move(-moveAmount * backgroundSpeed, 0.f);
            floor.move(-moveAmount * backgroundSpeed, 0.f);

        }

        if (!gameOver)
        {
            for (int i = 0; i < maxObstacles; i++)
            {
                if (!obstacles[i].isActive())
                {
                    obstacles[i].startSpawn(floor);
                }
                else
                {
                    obstacles[i].updatePosition(1.0f / 60.0f);
                    obstacles[i].checkCollisionWithPlayer(player);

                    if (rectangle.getGlobalBounds().intersects(obstacles[i].getShape().getGlobalBounds()))
                    {
                        std::cout << "COLLISION!" << std::endl;
                        gameOver = true;
                        break; 
                    }
                }
            } 
        }
        player.update(window);

        rectangle.setPosition(player.getX(), player.getY());

        window.setView(view);
        window.clear(sf::Color::Black);



        for (int i = 0; i < maxObstacles; i++)
        {
            obstacles[i].draw(window);
        }
        /*
        if (gameOver)
        {
            window.draw(gameOverText);
        }*/
        window.draw(rectangle);
        window.draw(floor);
        window.display();
    }


    return 0;
}