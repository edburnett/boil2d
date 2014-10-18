#include <DebugDraw.hpp>
#include <Functions.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

DebugDraw::DebugDraw():
    pixmeters(50.0f),
    radegrees(57.2957795f),
    m_target(0x0)
{
    AppendFlags(static_cast<uint32>(~0));

    // load font for strings
    if (!font.loadFromFile("resource/fonts/LeagueGothic-Regular.otf"))
    {
        std::cout << "Can't load font" << std::endl;
    }

    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color(55,55,55,200));
}

void DebugDraw::LinkTarget(sf::RenderTarget& gtarget)
{
    m_target = &gtarget;
}

//convert a Box2D (float 0.0f - 1.0f range) color to a SFML color (uint8 0 - 255 range)
sf::Color DebugDraw::B2SFColor(const b2Color &color, int alpha = 255)
{
    sf::Color result((sf::Uint8)(color.r*255), (sf::Uint8)(color.g*255), (sf::Uint8)(color.b*255), (sf::Uint8) alpha);
    //std::cout << "hit b2sfcolor" << std::endl;
    return result;
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape shape;
    shape.setOutlineColor(B2SFColor(color, 200));
    shape.setOutlineThickness(1);
    shape.setFillColor(B2SFColor(color, 24));
    shape.setPointCount(vertexCount);
    for(int i=0;i<vertexCount;++i)
    {shape.setPoint(i,EEVector(vertices[i]));}
    //m_target->draw(shape); 
    //std::cout << "hit DrawPolygon" << std::endl;
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
{
    sf::ConvexShape shape;
    shape.setFillColor(B2SFColor(color, 96));
    shape.setPointCount(vertexCount);
    for(int i = 0; i < vertexCount; ++i)
    {
        shape.setPoint(i,EEVector(vertices[i]));
    }
    m_target->draw(shape);

    //std::cout << "hit DrawSolidPolygon" << std::endl;
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{    
    sf::CircleShape shape;
    shape.setOutlineColor(B2SFColor(color, 200));
    shape.setOutlineThickness(1);
    //shape.setFillColor(sf::Color::Transparent);
    shape.setFillColor(B2SFColor(color, 0));
    shape.setRadius(radius*pixmeters);
    shape.setOrigin(sf::Vector2f(radius*pixmeters,radius*pixmeters));//set origin to middle or position setter below would not work correctly
    shape.setPosition(EEVector(center));
    m_target->draw(shape);

    std::cout << "hit DrawCircle" << std::endl;

}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    sf::CircleShape shape;
    shape.setOutlineColor(B2SFColor(color, 200));
    shape.setOutlineThickness(1);
    shape.setFillColor(B2SFColor(color, 96));
    shape.setRadius(radius*pixmeters);
    shape.setOrigin(sf::Vector2f(radius*pixmeters,radius*pixmeters));//set origin to middle or position setter below would not work correctly
    shape.setPosition(EEVector(center));
    m_target->draw(shape);
    //std::cout << "hit DrawSolidCircle" << std::endl;
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    sf::Vertex line[2];//const sized c styled array, safe enough in here
    line[0].color=B2SFColor(color, 200);
    line[0].position=EEVector(p1);
    line[1].color=B2SFColor(color, 200);
    line[1].position=EEVector(p2);
    m_target->draw(line,2,sf::Lines);
    std::cout << "hit DrawSegment" << std::endl;
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
    //std::cout << "hit DrawTransform" << std::endl;
}


void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
    sf::CircleShape shape(size);
    shape.setOutlineColor(B2SFColor(color, 200));
    shape.setFillColor(B2SFColor(color, 96));
    m_target->draw(shape);
    //std::cout << "hit DrawPoint" << std::endl;
}


void DebugDraw::DrawString(int x, int y, std::string str)
{
    text.setString(str);
    text.setPosition(x, y);
    m_target->draw(text);
}


void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color)
{
    //std::cout << "hit DrawAABB" << std::endl;
}



void DebugDraw::DrawMouseJoint(b2Vec2& p1, b2Vec2& p2, const b2Color &boxColor, const b2Color &lineColor)
{

    //std::cout << "hit DrawMouseJoint" << std::endl;
}
