#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct Collider {
    Collider(sf::RenderWindow* window, bool projectLines=false);
    Collider(sf::RenderWindow* window, float circle_radius, float circle_x, float circle_y, float line_x1, float line_y1, float line_x2, float line_y2, bool projectLines=false);


    bool pointCircle(float circle_radius, float circle_x, float circle_y, float point_x, float point_y);
    bool pointCircle(std::vector<float> circle, float point_x, float point_y);

    bool lineCircle(float circle_radius, float circle_x, float circle_y, float line_x1, float line_y1, float line_x2, float line_y2);

    void project();

    std::vector<float> line;
    std::vector<float> circle;

    private:
        sf::RenderWindow* _window;
        bool _projectLines;

        sf::Vertex line_a[2];
        sf::Vertex line_b[2];
};
