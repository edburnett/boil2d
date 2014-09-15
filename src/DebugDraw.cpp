#include <DebugDraw.hpp>
#include <Functions.hpp>

DebugDraw::DebugDraw()
{

}

//convert a Box2D (float 0.0f - 1.0f range) color to a SFML color (uint8 0 - 255 range)
sf::Color DebugDraw::B2SFColor(const b2Color &color, int alpha = 255)
{
    sf::Color result((sf::Uint8)(color.r*255), (sf::Uint8)(color.g*255), (sf::Uint8)(color.b*255), (sf::Uint8) alpha);
    return result;
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
   /* 
    sf::Shape polygon;
    for (int32 i=0; i<vertexCount; i++)
    {
        b2Vec2 vertex = vertices[i];
        polygon.AddPoint(vertex.x*RATIO, vertex.y*RATIO, this->B2SFColor(color, 50), this->B2SFColor(color, 255));
    }
    polygon.SetOutlineWidth(1.0f);
    polygon.EnableFill(false);
    this->app->draw(polygon);
    */
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
}
