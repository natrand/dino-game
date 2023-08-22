
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


    //window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dino Game");
    sf::Event ev;
    sf::View view(sf::FloatRect(0.f, 0.f, 800.f, 600.f)); //control view within the window

    sf::RectangleShape floor;
    floor.setSize(sf::Vector2f(window.getSize().x, 40)); // Set the size of the floor
    floor.setFillColor(sf::Color::Green); // Set the color of the floor
    floor.setPosition(0, window.getSize().y - floor.getSize().y); // Position the floor at the bottom of the window


    window.setFramerateLimit(60);

    //setting up square

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(50, 50));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(0, window.getSize().y - rectangle.getSize().y);

    Player player;
    const int maxObstacles = 5;
    Obstacles obstacles[maxObstacles];

    bool isJumping = false;
    bool gameStarted = false;


    //game loop
    while (window.isOpen())
    {
        //events
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape) //to exit we have to press esc button
                    window.close();

                //jumping
                else if (ev.key.code == sf::Keyboard::Space && !isJumping)
                {
                    player.jump();
                    player.update(window);
                    player.setVelocityY(-15.0f);
                    player.startGame();

                    isJumping = true;
                    gameStarted = true;
                }
                break;
            case sf::Event::KeyReleased:
                if (ev.key.code == sf::Keyboard::Space) {
                    isJumping = false;
                }
                break;
            }

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

        for (int i = 0; i < maxObstacles; i++)
        {
            obstacles[i].update(1.0f / 60.0f, player.getVelocityX(), floor);
        }

        player.update(window);

        rectangle.setPosition(player.getX(), player.getY());

        window.setView(view);
        window.clear(sf::Color::Black);

        window.draw(rectangle);
        window.draw(floor);

        for (int i = 0; i < maxObstacles; i++)
        {
            obstacles[i].draw(window);
        }


        window.display();
    }


    return 0;
}
