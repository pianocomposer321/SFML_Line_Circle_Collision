#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Collider.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(720, 720), "Line Circle Collider");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Vertex vertices[] = {
        sf::Vertex(sf::Vector2f(720/8, 720*3/4)),
        sf::Vertex(sf::Vector2f(720*3/4, 720/2))
        /* sf::Vertex(sf::Vector2f(100, 100), sf::Color::Red, sf::Vector2f(10, 10)), */
        /* sf::Vertex(sf::Vector2f(100,3), sf::Color::Red, sf::Vector2f(10,3)) */
    };

    sf::CircleShape circle;
    circle.setRadius(100.0f);
    circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
    circle.setPosition(720/2, 720/2);

    sf::FloatRect circleBounds = circle.getGlobalBounds();

    float circle_x = (circleBounds.left + circleBounds.width) / 2;
    float circle_y = (circleBounds.top + circleBounds.height) / 2;

    /* Collider collider ( */
    /*         circle.getRadius(), */
    /*         circle_x, */
    /*         circle_y, */
    /*         vertices[0].position.x, */
    /*         vertices[0].position.y, */
    /*         vertices[1].position.x, */
    /*         vertices[1].position.y */
    /* ); */

    Collider collider(&window);


    while (window.isOpen()) {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseMoved) {
                circleBounds = circle.getGlobalBounds();

                circle_x = circleBounds.left + circleBounds.width / 2;
                circle_y = circleBounds.top + circleBounds.height / 2;

                sf::Vector2i pos = sf::Mouse::getPosition(window);
                circle.setPosition(pos.x, pos.y);

                if (collider.pointCircle(circle.getRadius(), circle_x, circle_y, vertices[0].position.x, vertices[0].position.y)) {
                    std::cout << "Collision: point 1" << std::endl;
                }
                else if (collider.pointCircle(circle.getRadius(), circle_x, circle_y, vertices[1].position.x, vertices[1].position.y)) {
                    std::cout << "Collision: point 2" << std::endl;
                }
                else if (collider.lineCircle(
                    circle.getRadius(),
                    circle_x,
                    circle_y,
                    vertices[0].position.x,
                    vertices[0].position.y,
                    vertices[1].position.x,
                    vertices[1].position.y
                )) {
                    std::cout << "Collision: line" << std::endl;
                }
                else {
                    std::cout << "No collision" << std::endl;
                }

                /* std::cout << "Pos_x: " << pos.x << std::endl; */
                /* std::cout << "Pos_y: " << pos.y << std::endl; */
                /* std::cout << std::endl; */
            }
        }



        window.draw(vertices, 2, sf::Lines);
        collider.project();
        window.draw(circle);


        window.display();
    }

    return 0;

}
