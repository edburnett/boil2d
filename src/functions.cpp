#include <SFML/System.hpp>
#include <Functions.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>


sf::Vector2f meters_to_pixels(float xMeters, float yMeters)
{
    // assumes conversion rate of 50 pixels per meter
    return sf::Vector2f(50.0f * xMeters, 50.0f * yMeters);
}

sf::Vector2f pixels_to_meters(float xPixels, float yPixels)
{
    // assumes conversion rate of 50 pixels per meter
    return sf::Vector2f(0.02f * xPixels, 0.02f * yPixels);
}

float radians_to_degrees(float radians)
{
    float degrees = radians * (180/M_PI);
    std::cout << degrees << std::endl;
    return degrees;
}

float degrees_to_radians(float degrees)
{   
    float radians = degrees * (M_PI/180);
    std::cout << radians << std::endl;
    return radians;
}
