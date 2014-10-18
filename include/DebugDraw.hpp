#ifndef   DebugDraw_HPP_INCLUDED
#define   DebugDraw_HPP_INCLUDED

#include <Box2D/Box2D.h>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Functions.hpp>
#include <App.hpp>
#include <string>

class DebugDraw : public b2Draw
{
    private:
        sf::RenderTarget * m_target;

        inline sf::Color EEColor(const b2Color& gCol)
        {
            return sf::Color(static_cast<sf::Uint8>(255*gCol.r),
                            static_cast<sf::Uint8>(255*gCol.g),
                            static_cast<sf::Uint8>(255*gCol.b));
        }

        inline sf::Vector2f EEVector(const b2Vec2& gVec)
        {
            return sf::Vector2f(gVec.x*pixmeters,-gVec.y*pixmeters);
        }
        
        const float pixmeters,radegrees;

        sf::Font font;
        sf::Text text;

    public:
        DebugDraw();
        ~DebugDraw(){};
        
        void LinkTarget(sf::RenderTarget& gtarget);
        void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
        void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
        void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
        void DrawTransform(const b2Transform& xf);
        void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
        //void DrawString(int x, int y, const char* string);
        void DrawString(int x, int y, std::string str);
        void DrawAABB(b2AABB* aabb, const b2Color& color);
        sf::Color B2SFColor(const b2Color &color, int alpha);
        void DrawMouseJoint(b2Vec2& p1, b2Vec2& p2, const b2Color &boxColor, const b2Color &lineColor);

};

#endif
