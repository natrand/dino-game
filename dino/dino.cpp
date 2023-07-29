
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//setting fundamentals

float x = 0;
float y = 0;
float velocityX = 0;
float velocityY = 0;
float accX = 0;
float accY = 0;
float gravity = 1;

void update() {
    if (y < 500)
    {
        velocityY += gravity;
    }
    else if (y > 500)
    {
        y = 500;
    }
    velocityX += accX;
    velocityY += accY;

    x += velocityX;
    y += velocityY;
}

int main()
{
    //window
    sf::RenderWindow window(sf::VideoMode(800, 400), "Dino Game");
    sf::Event ev;
    //setting up square
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(50, 50));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(0, window.getSize().y - rectangle.getSize().y);

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
                else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space)
                {
                    velocityY = -10;
                }
                break;
            }

        }

        //moving object left and right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            velocityX = -2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            velocityX = 2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {

        }
        update();
        rectangle.setPosition(x, y);

        window.clear(sf::Color::White);
        window.draw(rectangle);
        window.display();
    }


    return 0;
}
