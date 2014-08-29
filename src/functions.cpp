#include <SFML/System.hpp>
#include <Functions.hpp>


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
