
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Game.h"



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

    Game game;

    bool isJumping = false;
    //bool gameStarted = false;

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
                    game.startGame();
                    game.update(window);
                    game.velocityY = -10;
                    isJumping = true;
                    //gameStarted = true;
                }
                break;
            case sf::Event::KeyReleased:
                if (ev.key.code == sf::Keyboard::Space) {
                    isJumping = false;
                }
                break;
            }

        }

        float moveAmount = 5.f;
        if (game.isGameStarted())
        {
            game.velocityX = 2;
            rectangle.move(moveAmount, 0.f);

            if (rectangle.getPosition().x + rectangle.getSize().x >= view.getCenter().x + view.getSize().x / 2) {
                view.move(moveAmount, 0.f); // Move the view to the right
                floor.move(moveAmount, 0.f);
            }

        }
        else {
            game.velocityX = 0;
        }

        game.update(window);
        rectangle.setPosition(game.x, game.y);

        window.setView(view);
        window.clear(sf::Color::Black);
        window.draw(rectangle);
        window.draw(floor);
        window.display();
    }


    return 0;
}
