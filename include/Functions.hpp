#ifndef   FUNCTIONS_HPP_INCLUDED
#define   FUNCTIONS_HPP_INCLUDED

#include <SFML/System.hpp>


sf::Vector2f meters_to_pixels(float xMeters, float yMeters);

sf::Vector2f pixels_to_meters(float xPixels, float yPixels);

float radians_to_degrees(float radians);

float degrees_to_radians(float degrees);

#endif
