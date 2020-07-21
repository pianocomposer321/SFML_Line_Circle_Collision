#define PI 3.141592653589793

#include <iostream>
#include <vector>
#include <cmath>

#include "Collider.h"


Collider::Collider(sf::RenderWindow* window, bool projectLines) {
    _window = window;
    _projectLines = projectLines;
}

Collider::Collider(sf::RenderWindow* window, float circle_radius, float circle_x, float circle_y, float line_x1, float line_y1, float line_x2, float line_y2, bool projectLines) {
    /* 
     * Rule of Cosines:
     * C^2 = A^2 + B^2 - 2AB Cos Y
     */

    _window = window;

    line = {line_x1, line_y1, line_x2, line_y2};
    circle = {circle_radius, circle_x, circle_y};
}

bool Collider::pointCircle(float circle_radius, float circle_x, float circle_y, float point_x, float point_y) {
    float distance = sqrt(pow(point_x - circle_x, 2) + pow(point_y - circle_y, 2));

    /* std::cout << "Radius: " << circle_radius << std::endl; */
    /* std::cout << "Circle_X: " << circle_x << std::endl; */
    /* std::cout << "Circle_Y: " << circle_y << std::endl; */
    /* std::cout << "Point_X: " << point_x << std::endl; */
    /* std::cout << "Point_Y: " << point_y << std::endl; */
    /* std::cout << "Distance: " << distance << std::endl; */
    /* std::cout << std::endl; */

    return distance < circle_radius;
}

bool Collider::pointCircle(std::vector<float> circle, float point_x, float point_y) {
    float distance = sqrt(pow(point_x - circle[0], 2) + pow(point_y - circle[1], 2));

    return distance < circle[2];
}

bool Collider::lineCircle(float circle_radius, float circle_x, float circle_y, float line_x1, float line_y1, float line_x2, float line_y2) {

    double distance_a = sqrt(pow(line_x1 - circle_x, 2) + pow(line_y1 - circle_y, 2));
    double distance_b = sqrt(pow(line_x1 - line_x2, 2) + pow(line_y1 - line_y2, 2));
    double distance_c = sqrt(pow(line_x2 - circle_x, 2) + pow(line_y2 - circle_y, 2));

    line_a[0] = sf::Vertex(sf::Vector2f(circle_x, circle_y));
    line_a[1] = sf::Vertex(sf::Vector2f(line_x1, line_y1));

    line_b[0] = sf::Vertex(sf::Vector2f(circle_x, circle_y));
    line_b[1] = sf::Vertex(sf::Vector2f(line_x2, line_y2));

    // Cosine Rule:
    // A^2 + B^2 - 2AB cos theta = C^2
    // -2AB cos theta = C^2 - A^2 - B^2
    // cos theta = (C^2 - A^2 - B^2)/-2AB
    // theta = acos(C^2 - A^2 - B^2)/-2AB

    double a_squared = pow(distance_a, 2);
    double b_squared = pow(distance_b, 2);
    double c_squared = pow(distance_c, 2);

    // sin theta = D / A
    // D = A * sin theta
    double angle_a = std::acos((c_squared - a_squared - b_squared) /
                               (-2 * distance_a * distance_b));


    double distance_d = distance_a * std::sin(angle_a);

    double temp = distance_a;
    distance_a = distance_b;
    distance_b = distance_c;
    distance_c = temp;

    a_squared = pow(distance_a, 2);
    b_squared = pow(distance_b, 2);
    c_squared = pow(distance_c, 2);

    double angle_b = std::acos((c_squared - a_squared - b_squared) /
                                           (-2 * distance_a * distance_b));

    double angle_a_degrees = angle_a * 180 / PI;
    double angle_b_degrees = angle_b * 180 / PI;

    if (distance_d < circle_radius && angle_a_degrees < 90 && angle_b_degrees < 90)
        return true;

    return false;
}

void Collider::project() {
    _window->draw(line_a, 2, sf::Lines);
    _window->draw(line_b, 2, sf::Lines);
}
